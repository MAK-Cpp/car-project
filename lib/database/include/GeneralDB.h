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

const std::map<std::string, std::pair<double, std::string>> price_coefficient {{"Минск" , {0.037, "Бел. руб."}},
                                                       {"Москва", {1., "Руб."}},
                                                       {"Санкт-Петербург", {1., "Руб."}},
                                                       {"Вашингтон", {0.012, "Долл."}}};

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

    static bool insert_sell(uint64_t user_id_s, uint64_t car_id_s, QDate start_date_s, QDate end_date_s, uint64_t total_sum_s);

    static std::vector<std::tuple<uint64_t, QDate, QDate, uint64_t>> get_rented_car(uint64_t user_id);
};

#endif //CAR_PROJECT_GENERALDB_H
