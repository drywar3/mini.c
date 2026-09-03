cmake_minimum_required(VERSION 4.2)
project(mini.c LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(MINI_C_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
file(GLOB_RECURSE SOURCES src/*.c)

add_library(mini.c STATIC ${SOURCES})
target_include_directories(mini.c PRIVATE ./include/)
