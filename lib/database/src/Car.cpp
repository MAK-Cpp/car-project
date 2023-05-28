#include "Car.h"

Car::Car(uint64_t id,
         std::string name,
         uint64_t price,
         uint64_t consumption,
         uint64_t capacity,
         std::string fuel,
         std::string picture_path,
         std::string city,
         std::string color,
         std::string brand) :
    id{id},
    name{name},
    price{price},
    consumption{consumption},
    capacity{capacity},
    fuel{fuel},
    picture_path{picture_path},
    city{city},
    color{color},
    brand{brand} {}
