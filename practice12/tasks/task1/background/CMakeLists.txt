# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes

add_library(background background.c)
include_directories("../pipes")
target_link_libraries(background pipes)
