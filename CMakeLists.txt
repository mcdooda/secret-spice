cmake_minimum_required(VERSION 2.6)

project(beatshapt)

file(
    GLOB_RECURSE
    src
    src/*
)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(
    beatshapt
    ${src}
)

target_link_libraries(
    beatshapt
    SDL
    SDL_image
    SDL_ttf
    GL
    GLU
    GLEW
)
