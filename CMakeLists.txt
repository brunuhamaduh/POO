cmake_minimum_required(VERSION 3.23)
project(POO)

set(CMAKE_CXX_STANDARD 14)

add_executable(POO Terminal.cpp main.cpp Coordenadas.cpp Coordenadas.h Animal.cpp Animal.h Alimento.cpp Alimento.h Reserva.cpp Reserva.h Functions.cpp Functions.h)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/pdcurses.a)