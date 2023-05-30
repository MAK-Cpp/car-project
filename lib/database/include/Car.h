#ifndef CARPROJECT_LIB_DATABASE_INCLUDE_CAR_H_
#define CARPROJECT_LIB_DATABASE_INCLUDE_CAR_H_

#include <string>


class Car {
private:
public:
    uint64_t car_id;
    std::string name;
    uint64_t price;
    uint64_t consumption;
    uint64_t capacity;
    std::string fuel;
    std::string picture_path;
    std::string town;
    std::string color;
    std::string brand;
    Car(uint64_t id, std::string name, uint64_t price, uint64_t consumption, uint64_t capacity,
        std::string fuel, std::string picture_path, std::string town, std::string color, std::string brand);
};

#endif //CARPROJECT_LIB_DATABASE_INCLUDE_CAR_H_
