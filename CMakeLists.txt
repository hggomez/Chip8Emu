cmake_minimum_required(VERSION 3.10)
project(chip8emu)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8emu main.cpp cpu.h cpu.cpp chip8stack.hpp chip8memory.hpp chip8display.h chip8display.cpp suffixes.hpp)
target_link_libraries(chip8emu ${SDL2_LIBRARIES})