cmake_minimum_required(VERSION 3.26)
project(Life)

set(CMAKE_CXX_STANDARD 20)

add_executable(LifeTest main.cpp
        game/Game.cpp
        game/Game.h
        main.cpp)

add_library(Life library.cpp
        game/Game.cpp
        game/Game.h)
