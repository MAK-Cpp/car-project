#include "Car.h"

Car::Car(uint64_t car_id,
         std::string name,
         uint64_t price,
         uint64_t consumption,
         uint64_t capacity,
         std::string fuel,
         std::string picture_path,
         std::string towm,
         std::string color,
         std::string brand) :
    car_id{car_id},
    name{name},
    price{price},
    consumption{consumption},
    capacity{capacity},
    fuel{fuel},
    picture_path{picture_path},
    town{towm},
    color{color},
    brand{brand} {}
