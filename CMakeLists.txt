cmake_minimum_required(VERSION 3.23)
project(TP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP Terminal.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} C:/Users/brunuh/CLionProjects/TP/pdcurses.a)