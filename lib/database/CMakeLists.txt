include_directories(include)
add_library(Car include/Car.h src/Car.cpp)
link_libraries(Car)
add_library(GeneralDB include/GeneralDB.h src/GeneralDB.cpp)
set(DATABASE_LIBRARIES GeneralDB Car PARENT_SCOPE)

