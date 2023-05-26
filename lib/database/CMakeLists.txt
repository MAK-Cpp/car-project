include_directories(include)
add_library(UserDB include/UserDB.h src/UserDB.cpp)
set(DATABASE_LIBRARIES UserDB PARENT_SCOPE)