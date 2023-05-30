#include "GeneralDB.h"
#include <string>
#include <algorithm>
#include <iostream>
#include "QDate"

/**
 * Преобразует @b QString в @b std::string
 *
 * @param x @b QString переменная
 * @return @b std::string, содержащая текст из @b QString
 */
std::string toStdString(const QString &x) {
    return std::string{x.toUtf8().data()};
}

/**
 * Подключается к БД, вызывается один раз при запуске программы.
 *
 * @throw std::filesystem::filesystem_error если при открытии БД произошла ошибка.
 */
void GeneralDB::init() {
    int flag;
    char *zErrMsg = 0;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR   "/database/car_project.db");
    flag = sqlite3_open(database_path.string().c_str(), &data_base_);
    if (flag != 0) {
        throw std::filesystem::filesystem_error("Can't open database!!!", std::error_code());
    }
}

GeneralDB::~GeneralDB() {
    sqlite3_close(data_base_);
}

std::vector<Car> GeneralDB::getAllCars() {
    std::vector<Car> result;
    sqlite3_stmt *stmt;
    std::string total_query = "SELECT * FROM cars";
    sqlite3_prepare_v2(data_base_, total_query.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        uint64_t car_id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        uint64_t price = sqlite3_column_int(stmt, 2);
        uint64_t consumption = sqlite3_column_double(stmt, 3);
        uint64_t capacity = sqlite3_column_double(stmt, 4);
        std::string fuel = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        std::string picture_path = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::string town = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
        std::string color = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
        std::string brand = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
        result.emplace_back(Car(car_id,
                                name,
                                price,
                                consumption,
                                capacity,
                                fuel,
                                picture_path,
                                town,
                                color,
                                brand));
    }
    return result;
}

/**
 * Пытается залогинить пользователя.
 *
 * @param login_s логин пользователя
 * @param password_s пароль пользователя
 * @return access::NONE, если пользователь не зарегистрирован
 * @return access::USER, если вошел обычный пользователь
 * @return access::ROOT, если зашел администратор
 */
access GeneralDB::check_user(QString login_s, QString password_s) {
    sqlite3_stmt *stmt;
    std::string query = "SELECT login, password, root FROM users";
    sqlite3_prepare_v2(data_base_, query.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string login = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int root = sqlite3_column_int(stmt, 2);
        if (QString::fromStdString(login) == login_s && QString::fromStdString(password) == password_s) {
            if (root == 1) {
                return access::USER;
            }
            return access::ROOT;
        }
    }
    return access::NONE;
}

/**
 * Регистрирует нового пользователя.
 *
 * @param name_s имя пользователя
 * @param login_s логин пользователя
 * @param password_s пароль пользователя
 * @throw std::runtime_error если не получилось зарегистрировать пользователя.
 * @returns @b reg_const::NONE, если пользователь уже есть в БД
 * @returns @b reg_const::COMPLETE, иначе
 */
reg_const GeneralDB::register_user(QString name_s, QString login_s, QString password_s) {
    char *zErrMsg;
    sqlite3_stmt *stmt;
    int rc;
    std::string query = "SELECT login, password FROM users";
    sqlite3_prepare_v2(data_base_, query.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string login = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        if (QString::fromStdString(login) == login_s) {
            return reg_const::NONE;
        }
    }
    query = "INSERT INTO users (name, login, password, root) VALUES ('" + toStdString(name_s) + "', '"
        + toStdString(login_s) +
        "', '" + toStdString(password_s) + "', 1)";
    rc = sqlite3_exec(data_base_, query.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error(zErrMsg);
    }
    return reg_const::COMPLETE;
}

/**
 * Возвращает @b std::vector\<@b Car\>, содержащий все машины, доступные в выбранное время.
 *
 * @param line_s строка, содержащая запрос пользователя по типу машины
 * @param users_start_date строка, содержащая стартовую дату
 * @param users_end_date строка, содержащая конечную дату
 * @return @b std::vector\<@b Car\> машин, подходящих под параметры запроса
 */
std::vector<uint64_t> GeneralDB::select_cars(QString line_s, QDate users_start_date, QDate users_end_date) {
    std::vector<uint64_t> cars_id;
    sqlite3_stmt *stmt1;
    int rc;
    bool flag = true;
    std::string query = "SELECT DISTINCT car_id FROM cars WHERE name LIKE '%" + toStdString(line_s) + "%'";
    sqlite3_prepare_v2(data_base_, query.c_str(), -1, &stmt1, nullptr);
    while (sqlite3_step(stmt1) == SQLITE_ROW) {
        int car_id = sqlite3_column_int(stmt1, 0);
        sqlite3_stmt *stmt2;
        flag = true;
        std::string one_query = "SELECT start_date, end_date FROM sells WHERE car_id = " + std::to_string(car_id);
        sqlite3_prepare_v2(data_base_, one_query.c_str(), -1, &stmt2, nullptr);
        while (sqlite3_step(stmt2) == SQLITE_ROW) {
            QDate start_date = QDate::fromString(reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 0)), "dd-MM-yyyy");
            QDate end_date = QDate::fromString(reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 1)), "dd-MM-yyyy");
            if (end_date < users_start_date || users_end_date < start_date) {
                continue;
            } else {
                flag = false;
                break;
            }
        }
        if (flag) {
            cars_id.emplace_back(car_id);
        }
    }
    return cars_id;
}

bool GeneralDB::insert_sell(QString user_id_s, QString car_id_s, QDate start_date_s, QDate end_date_s, int total_sum_s){
    char *zErrMsg;
    sqlite3_stmt *stmt;
    int rc;
    std::string query = "INSERT INTO sells (user_id, car_id, start_date, end_date, ) VALUES ('" + toStdString(user_id_s) + "', '"
            + toStdString(car_id_s) +
            "', '" + toStdString(start_date_s.toString("dd-MM-yyyy")) + "', '" + toStdString(end_date_s.toString("dd-MM-yyyy")) + "', "
            + std::to_string(total_sum_s) + ")";
    rc = sqlite3_exec(data_base_, query.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error(zErrMsg);
    }
    return true;
}

bool GeneralDB::insert_car(Car const &new_car){
    char *zErrMsg;
    sqlite3_stmt *stmt;
    int rc;
    std::string query = "INSERT INTO cars (name, price, consumption, capacity, fuel, picture_path, town, color, brand) VALUES ('" + new_car.name + "', "
                        + std::to_string(new_car.price)+ ", " + std::to_string(new_car.consumption) + ", " + std::to_string(new_car.capacity) + ", '"
                        + new_car.fuel + "', '" + new_car.picture_path + "', '" + new_car.city + "', '" + new_car.color + "', '" + new_car.brand + "')";
    rc = sqlite3_exec(data_base_, query.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        throw std::runtime_error(zErrMsg);
    }
    return true;
}