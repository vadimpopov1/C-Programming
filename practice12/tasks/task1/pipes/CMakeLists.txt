# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.c

project(pipes)
file(GLOB SOURCES "*.c")
add_library(pipes ${SOURCES})
