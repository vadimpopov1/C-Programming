#include "../include/typing_trainer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Проверка на принятие уровней и проверку если подавать на ввод неверные
void test_validation() {
    printf("Testing validation...\n");
    
    assert(validate_difficulty(1) == 1);  // Beginner
    assert(validate_difficulty(2) == 1);  // Intermediate
    assert(validate_difficulty(3) == 1);  // Advanced
    
    // Проверяем недопустимые значения
    assert(validate_difficulty(0) == 0);
    assert(validate_difficulty(4) == 0);
    
    printf("Validation passed\n");
}

// Тест на генерацию текста в зависимости от уровня сложности и от режима
void test_text_generation() {
    printf("Testing text generation...\n");
    
    // Проверяем генерацию текста с числовыми уровнями
    const char* word = get_random_text(1, 1); // Beginner level
    assert(word != NULL);
    
    const char* sentence = get_random_text(2, 2); // Intermidate level
    assert(sentence != NULL);
    
    printf("Text generation passed\n");
}

// Проверяем на строке test и проверяет корректеые числа
void test_typing_basic() {
    printf("Testing basic typing...\n");
    
    const char* text = "test";
    TestResult res = run_typing_test(text);
    
    assert(res.correct >= 0);
    assert(res.incorrect >= 0);
    
    printf("Typing test passed\n");
}

int main() {
    printf("\nStarting tests...\n");
    
    test_validation();
    test_text_generation();
    test_typing_basic();
    
    printf("\nAll tests passed!\n");
    return 0;
}