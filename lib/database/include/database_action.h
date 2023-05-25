#ifndef CAR_PROJECT_DATABASE_ACTION_H
#define CAR_PROJECT_DATABASE_ACTION_H
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"
#include <QString>

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

std::vector<Car> select_cars(std::string start_date, std::string end_date, std::string query = "");

enum class access : uint8_t {NONE, USER, ROOT};

access check_user(QString login, QString password);

bool insert_car(Car const &new_car);

bool delete_car(int id);



#endif //CAR_PROJECT_DATABASE_ACTION_H
