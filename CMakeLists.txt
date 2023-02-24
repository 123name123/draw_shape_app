cmake_minimum_required(VERSION 3.24)
project(shape_app)

set(CMAKE_CXX_STANDARD 20)

add_executable(shape_app main.cpp shapes.h shapes.cpp)
