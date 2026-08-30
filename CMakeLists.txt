cmake_minimum_required(VERSION 4.2)
project(mini.c LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.c)

add_library(mini.c ${SOURCES})
target_include_directories(mini.c PRIVATE ./include/)