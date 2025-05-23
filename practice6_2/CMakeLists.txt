cmake_minimum_required(VERSION 3.10)
project(practice6_2)

set(CMAKE_C_STANDARD 11)

option(USE_STATIC_LIB "Use static library" ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SOURCE_FILES src/main.c src/train_input_output.c src/train_search.c)
include_directories(include)

if(USE_STATIC_LIB)
    add_library(train STATIC src/train_input_output.c src/train_search.c) # Создаем статическую библиотеку
else()
    add_library(train SHARED src/train_input_output.c src/train_search.c) # Создаем динамическую библиотеку
endif()


add_library(train_lib 
    src/train_input_output.c 
    src/train_search.c
)

add_executable(practice6_2 src/main.c)

target_link_libraries(practice6_2 train_lib)

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for MacOS" FORCE)
endif()