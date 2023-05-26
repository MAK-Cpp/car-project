#include "UserDB.h"

Car::Car(QString name, QString id, QString price, QString consumption, QString capacity,
         QString fuel, QString picture_path, QString town):name{std::move(name)}, id{id},
                                                           price{price}, consumption{consumption}, capacity{capacity}, fuel{fuel},
                                                           picture_path{picture_path}, town{town}{
}

void UserDB::init() {
    int flag;
    char *zErrMsg = 0;
    std::filesystem::path const database_path(PROJECT_SOURCE_DIR  "/database/car_project.db");
    flag = sqlite3_open(database_path.string().c_str(), &data_base_);
    if(flag != 0) {
        throw std::filesystem::filesystem_error("Cant open database!!!", std::error_code());
    }
}

UserDB::~UserDB() {
    sqlite3_close(data_base_);
    delete data_base_;
}

access UserDB::check_user(QString login_s, QString password_s){
    sqlite3_stmt *stmt;
    std::string query = "SELECT login, password, root FROM users";
    sqlite3_prepare_v2(data_base_, query.c_str(), -1, &stmt, nullptr);
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


reg_const UserDB::register_user(QString name_s, QString login_s, QString password_s){
    char* zErrMsg;
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
    query = "INSERT INTO users (name, login, password, root) VALUES ('" + name_s.toStdString() + "', '" + login_s.toStdString() +
            "', '" + password_s.toStdString() + "', 1)";
    rc = sqlite3_exec(data_base_, query.c_str(), 0, 0, &zErrMsg);
    if(rc != SQLITE_OK){
        throw std::runtime_error(zErrMsg);
    }
    return reg_const::COMPLETE;
}