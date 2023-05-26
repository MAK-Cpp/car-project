#include "GeneralDB.h"
#include <string>
#include <algorithm>
#include <iostream>

std::string toStdString(const QString &x) {
    return std::string{x.toUtf8().data()};
}

Car::Car(QString name, QString id, QString price, QString consumption, QString capacity,
         QString fuel, QString picture_path, QString town) : name{std::move(name)},
                                                             id{id},
                                                             price{price},
                                                             consumption{consumption},
                                                             capacity{capacity},
                                                             fuel{fuel},
                                                             picture_path{picture_path},
                                                             town{town} {
}

void GeneralDB::init() {
    int flag;
    char *zErrMsg = 0;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR  "/database/car_project.db");
    flag = sqlite3_open(database_path.string().c_str(), &data_base_);
    if (flag != 0) {
        throw std::filesystem::filesystem_error("Cant open database!!!", std::error_code());
    }
}

GeneralDB::~GeneralDB() {
    sqlite3_close(data_base_);
}

bool isDateEarlier(std::string date1, std::string date2) {
    int day1, month1, year1;
    int day2, month2, year2;

    sscanf(date1.c_str(), "%d-%d-%d", &day1, &month1, &year1);
    sscanf(date2.c_str(), "%d-%d-%d", &day2, &month2, &year2);

    if (year1 < year2) {
        return true;
    } else if (year1 > year2) {
        return false;
    }

    if (month1 < month2) {
        return true;
    } else if (month1 > month2) {
        return false;
    }

    if (day1 < day2) {
        return true;
    } else if (day1 > day2) {
        return false;
    }

    return true;
}
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

std::vector<Car> GeneralDB::select_cars(QString line_s, QString start_date_s, QString end_date_s) {
    std::vector<Car> result;
    std::vector<int> cars_id;
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
            std::string start_date = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 0));
            std::string end_date = reinterpret_cast<const char *>(sqlite3_column_text(stmt2, 1));
            if ((isDateEarlier(start_date, toStdString(end_date_s)) &&
                isDateEarlier(toStdString(start_date_s), start_date)) ||
                (isDateEarlier(end_date, toStdString(end_date_s)) &&
                    isDateEarlier(toStdString(start_date_s), end_date))) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cars_id.emplace_back(car_id);
        }
    }
    sqlite3_stmt *stmt;
    std::string total_query = "SELECT * FROM cars";
    sqlite3_prepare_v2(data_base_, total_query.c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int car_id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        int price = sqlite3_column_int(stmt, 2);
        double consumption = sqlite3_column_double(stmt, 3);
        double capacity = sqlite3_column_double(stmt, 4);
        double fuel = sqlite3_column_double(stmt, 5);
        std::string picture_path = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
        std::string town = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
        auto it = std::find(cars_id.begin(), cars_id.end(), car_id);
        if (it != cars_id.end()) {
            result.emplace_back(Car(QString::fromStdString(std::to_string(car_id)),
                                    QString::fromStdString(name),
                                    QString::fromStdString(std::to_string(price)),
                                    QString::fromStdString(std::to_string(consumption)),
                                    QString::fromStdString(std::to_string(capacity)),
                                    QString::fromStdString(std::to_string(fuel)),
                                    QString::fromStdString(picture_path),
                                    QString::fromStdString(town)));
        }
    }
    return result;
}