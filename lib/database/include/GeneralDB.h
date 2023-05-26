#ifndef CAR_PROJECT_GENERALDB_H
#define CAR_PROJECT_GENERALDB_H
#include <filesystem>
#include "sqlite3.h"
#include "QString"
enum class access : uint8_t {NONE, USER, ROOT};
enum class reg_const : uint8_t {NONE, COMPLETE};

class Car {
private:
public:
    QString name;
    QString id;
    QString price;
    QString consumption;
    QString capacity;
    QString fuel;
    QString picture_path;
    QString town;
    Car(QString name, QString id, QString price, QString consumption, QString capacity,
        QString fuel, QString picture_path, QString town);
};


class GeneralDB {
private:
    inline static sqlite3 *data_base_ = nullptr;
    GeneralDB() = default;
public:
    static void init();

    ~GeneralDB();

    static reg_const register_user(QString name_s, QString login_s, QString password_s);

    static access check_user(QString login_s, QString password_s);

    static bool insert_car(Car const &new_car);

    static bool delete_car(int id);
};

#endif //CAR_PROJECT_GENERALDB_H
