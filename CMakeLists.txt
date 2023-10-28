cmake_minimum_required(VERSION 3.26)
project(Life)

set(CMAKE_CXX_STANDARD 20)

add_executable(LifeTest main.cpp game/Game.cpp
        game/Game.h
        game/resources/Resource.cpp
        game/resources/Resource.h
        game/GameManager.cpp
        game/GameManager.h
        game/resources/Building.cpp
        game/resources/Building.h
        game/effects/Effect.cpp
        game/effects/Effect.h
        game/utils/IO.cpp
        game/utils/IO.h
        game/effects/Requirement.cpp
        game/effects/Requirement.h
        game/effects/EffectTarget.h
        game/resources/Cost.cpp
        game/resources/Cost.h
)

add_library(Life SHARED library.cpp game/Game.cpp
        game/Game.h
        game/resources/Resource.cpp
        game/resources/Resource.h
        game/GameManager.cpp
        game/GameManager.h
        game/resources/Building.cpp
        game/resources/Building.h
        game/effects/Effect.cpp
        game/effects/Effect.h
        game/utils/IO.cpp
        game/utils/IO.h
        game/effects/Requirement.cpp
        game/effects/Requirement.h
        game/effects/EffectTarget.h
        game/resources/Cost.cpp
        game/resources/Cost.h
)

# json_cpp library

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(Life PRIVATE JsonCpp::JsonCpp)
target_link_libraries(LifeTest PRIVATE JsonCpp::JsonCpp)

# fmt library

find_package(fmt CONFIG REQUIRED)
target_link_libraries(Life PRIVATE fmt::fmt)
target_link_libraries(LifeTest PRIVATE fmt::fmt)

# add resources directory for the test

add_custom_command(TARGET LifeTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:LifeTest>/resources)