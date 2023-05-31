#ifndef CAR_PROJECT_GENERALDB_H
#define CAR_PROJECT_GENERALDB_H
#include <filesystem>
#include <QDate>
#include <map>
#include <set>
#include "sqlite3.h"
#include "QString"
#include "Car.h"
#include "QDate"
enum class access : uint8_t { NONE, USER, ROOT };
enum class reg_const : bool { NONE, COMPLETE };

const std::map<std::string, double> price_coefficient {{"Минск" , 0.037},
                                                       {"Москва", 1.},
                                                       {"Санкт-Петербург", 1.},
                                                       {"Вашингтон", 0.012}};

class GeneralDB {
private:
    inline static sqlite3 *data_base_ = nullptr;
    GeneralDB() = default;
public:
    static void init();

    ~GeneralDB();

    static std::vector<Car> getAllCars();

    static reg_const register_user(QString name_s, QString login_s, QString password_s);

    static std::pair<int, access> check_user(QString login_s, QString password_s);

    static std::set<uint64_t> select_cars(QString line_s, QDate users_start_date, QDate users_end_date, QString town_s);

    static bool insert_car(Car const &new_car);

    static bool delete_car(int id);

    static bool insert_sell(QString user_id_s, QString car_id_s, QDate start_date_s, QDate end_date_s, int total_sum_s);
};

#endif //CAR_PROJECT_GENERALDB_H
