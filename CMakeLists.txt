cmake_minimum_required(VERSION 3.23)
project(POO)

set(CMAKE_CXX_STANDARD 14)

add_executable(POO Headers/Terminal.cpp main.cpp Headers/Coordenadas.cpp Headers/Coordenadas.h Headers/Animal.cpp Headers/Animal.h Headers/Alimento.cpp Headers/Alimento.h Headers/Reserva.cpp Headers/Reserva.h Headers/Functions.cpp Headers/Functions.h)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/Headers/pdcurses.a)