#include "database_action.h"

Car::Car(QString name, QString id, QString price, QString consumption, QString capacity,
         QString fuel, QString picture_path, QString town):name{std::move(name)}, id{id},
         price{price}, consumption{consumption}, capacity{capacity}, fuel{fuel},
         picture_path{picture_path}, town{town}{
}

std::vector<Car> select_cars(std::string query){
    sqlite3 *db;
    int flag;
    std:: vector<Car> result;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR  "/database/car_project.db");
    return result;
}

access check_user(QString login_s, QString password_s){
    sqlite3 *db;
    int flag;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR  "/database/car_project.db");
    flag = sqlite3_open(database_path.string().c_str(), &db);
    if (flag) {
        return access::ERROR;
    } else {
        sqlite3_stmt *stmt;
        std::string query = "SELECT login, password, root FROM users";
        sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string login = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int root = sqlite3_column_int(stmt, 2);
            if(QString::fromStdString(login) == login_s && QString::fromStdString(password) == password_s){
                if(root == 1){
                    return access::USER;
                }
                return access::ROOT;
            }
        }
        return access::NONE;
    }
}

reg_const register_user(QString name_s, QString login_s, QString password_s){
    sqlite3 *db;
    int flag;
    char *zErrMsg = 0;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR  "/database/car_project.db");
    flag = sqlite3_open(database_path.string().c_str(), &db);
    if (flag) {
        return reg_const::ERROR;
    } else {
        sqlite3_stmt *stmt;
        int rc;
        std::string query = "SELECT login, password FROM users";
        sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string login = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            std::string password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            if (QString::fromStdString(login) == login_s) {
                return reg_const::NONE;
            }
        }
        query = "INSERT INTO users (name, login, password, root) VALUES ('" + std::string{name_s.toUtf8().data()} + "', '" + std::string{login_s.toUtf8().data()} +
                "', '" + std::string{password_s.toUtf8().data()} + "', 1)";
        rc = sqlite3_exec(db, query.c_str(), 0, 0, &zErrMsg);
        return reg_const::COMPLETE;
    }
}