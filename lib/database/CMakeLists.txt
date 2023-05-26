include_directories(include)
add_library(database_action include/database_action.h src/database_action.cpp)

set(${DATABASE_LIBRARIES} database_action PARENT_SCOPE)