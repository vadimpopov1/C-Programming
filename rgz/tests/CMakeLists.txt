add_executable(test_typing_trainer test_typing_trainer.c ../src/typing_trainer.c ../src/validation.c)
target_include_directories(test_typing_trainer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME test_typing_trainer COMMAND test_typing_trainer)