cmake_minimum_required(VERSION 3.20)
project(tetris LANGUAGES CXX)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp
    tasks.md
    gamestate.h
    introstate.h introstate.cpp
    texture.h texture.cpp
    abstracttexture.h
    texttexture.h texttexture.cpp
    abstracttexture.cpp
    appstate.h appstate.cpp
    statemanager.h statemanager.cpp
    exitstate.h exitstate.cpp
    playstate.h playstate.cpp
    component.h
    boardcomponent.h boardcomponent.cpp
    tetronomio.h tetronomio.cpp
    collidable.h
    timer.h timer.cpp
    gameoverstate.h gameoverstate.cpp)

file(COPY roboto.ttf DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
