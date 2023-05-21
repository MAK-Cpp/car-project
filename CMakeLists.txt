cmake_minimum_required(VERSION 3.25)
project(Project)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL 3.2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

add_executable(main src/main.cpp)

target_link_libraries(main OpenGL::GL glfw GLEW::glew)