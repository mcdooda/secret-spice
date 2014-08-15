cmake_minimum_required(VERSION 2.6)

project(secret-spice)

file(
    GLOB_RECURSE
    src
    src/*
    flat/src/*
)

include_directories(flat/src)

set(CMAKE_CXX_FLAGS "-g -Wall -O0")
#set(CMAKE_CXX_FLAGS "-O3")

add_executable(
    secret-spice
    ${src}
)

target_link_libraries(
    secret-spice
    SDL2
    SDL2_image
    SDL2_mixer
    SDL_ttf
    GL
    GLU
    GLEW
    essentia
    avcodec
    avformat
    avutil
    yaml
    fftw3f
    tag
    samplerate
)
