cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Widgets Gui UiTools REQUIRED)
find_package(SQLite3 REQUIRED)

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

set(LIBRARIES Qt6::Core Qt6::Widgets Qt6::Gui Qt6::UiTools SQLite3)


link_libraries(${LIBRARIES})


add_subdirectory(lib)


add_executable(main src/main.cpp)


target_link_libraries(main PRIVATE ${GUI_LIBRARIES} ${DATABASE_LIBRARIES})
target_include_directories(main PRIVATE lib/GUI/include lib/database/include)
