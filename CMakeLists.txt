cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_definitions( -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

set(LIBRARIES Qt::Core Qt::Widgets Qt::Gui SQLite3)


link_libraries(${LIBRARIES})


add_subdirectory(lib)


add_executable(main src/main.cpp)
set_target_properties(main PROPERTIES AUTOMOC TRUE)



target_link_libraries(main PRIVATE ${GUI_LIBRARIES} ${DATABASE_LIBRARIES})
target_include_directories(main PRIVATE lib/GUI/include lib/database/include)
