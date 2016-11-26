cmake_minimum_required(VERSION 3.6)
project(PokemonGo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ColaPrior.hpp
    coordenada.cpp
    Coordenada.h
    DiccString.hpp
    Driver.cpp
    Driver.h
    juego.cpp
    Juego.h
    mapa.cpp
    Mapa.h
    tests.cpp
    TiposJuego.h)

add_executable(PokemonGo ${SOURCE_FILES})