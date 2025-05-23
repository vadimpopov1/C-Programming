cmake_minimum_required(VERSION 3.10)
project(TypingTrainer C)

set(CMAKE_C_STANDARD 11)

add_executable(typing_trainer 
    src/main.c 
    src/typing_trainer.c 
    src/validation.c
)

enable_testing()
add_subdirectory(tests)

target_include_directories(typing_trainer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)