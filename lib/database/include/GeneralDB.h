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
    QString id;
    QString name;
    QString price;
    QString consumption;
    QString capacity;
    QString fuel;
    QString picture_path;
    QString town;
    Car(QString id, QString name, QString price, QString consumption, QString capacity,
        QString fuel, QString picture_path, QString town);
};


class GeneralDB {
private:
    inline static sqlite3 *data_base_;
    GeneralDB() = default;
public:
    static void init();

    ~GeneralDB();

    static reg_const register_user(QString name_s, QString login_s, QString password_s);

    static access check_user(QString login_s, QString password_s);

    static std::vector<Car> select_cars(QString line_s, QString start_date_s, QString end_date_s);

    static bool insert_car(Car const &new_car);

    static bool delete_car(int id);
};

#endif //CAR_PROJECT_GENERALDB_H
