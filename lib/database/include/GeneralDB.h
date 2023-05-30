#ifndef CAR_PROJECT_GENERALDB_H
#define CAR_PROJECT_GENERALDB_H
#include <filesystem>
#include <QDate>
#include "sqlite3.h"
#include "QString"
#include "Car.h"
#include "QDate"
enum class access : uint8_t { NONE, USER, ROOT };
enum class reg_const : bool { NONE, COMPLETE };


class GeneralDB {
private:
    inline static sqlite3 *data_base_ = nullptr;
    GeneralDB() = default;
public:
    static void init();

    ~GeneralDB();

    static std::vector<Car> getAllCars();

    static reg_const register_user(QString name_s, QString login_s, QString password_s);

    static access check_user(QString login_s, QString password_s);

    static std::vector<uint64_t> select_cars(QString line_s, QDate users_start_date, QDate users_end_date);

    static bool insert_car(Car const &new_car);

    static bool delete_car(int id);

    static bool insert_sell(QString user_id_s, QString car_id_s, QDate start_date_s, QDate end_date_s, int total_sum_s);
};

#endif //CAR_PROJECT_GENERALDB_H
