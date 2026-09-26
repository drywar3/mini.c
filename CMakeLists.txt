cmake_minimum_required(VERSION 4.2)
project(mini.c LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB_RECURSE CC_SOURCES src/mini.cc/*.cpp)

add_library(mini.c STATIC ${SOURCES})
target_include_directories(mini.c PRIVATE ./include/)
target_compile_options(mini.c PRIVATE
    -Wno-return-type-c-linkage
)

add_library(mini.cc STATIC ${CC_SOURCES})
target_include_directories(mini.cc PRIVATE ./include/)
target_link_libraries(mini.cc PRIVATE mini.c)
target_compile_options(mini.cc PRIVATE
    -Wno-return-type-c-linkage
)
