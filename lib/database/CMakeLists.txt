include_directories(include)
add_library(GeneralDB include/GeneralDB.h src/GeneralDB.cpp)
set(DATABASE_LIBRARIES GeneralDB PARENT_SCOPE)