cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 3.2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(SQLite3 REQUIRED)

message(${PROJECT_SOURCE_DIR})

add_definitions( -DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

link_libraries(OpenGL::GL glfw GLEW::glew SQLite3)

add_subdirectory(lib)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE button)
target_include_directories(main PRIVATE lib)
