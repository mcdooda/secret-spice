cmake_minimum_required(VERSION 2.6)

project(beatshapt)

file(
    GLOB_RECURSE
    src
    src/*
)

set(CMAKE_CXX_FLAGS "-g -Wall -O0")
#set(CMAKE_CXX_FLAGS "-O3")

add_executable(
    beatshapt
    ${src}
)

target_link_libraries(
    beatshapt
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
