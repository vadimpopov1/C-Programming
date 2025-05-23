#include "typing_trainer.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    DifficultyLevel level;
    TrainingMode mode;
    int test_time;
    
    while (1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1 || !validate_menu_choice(choice)) {
            while (getchar() != '\n'); 
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("\nSelect difficulty:\n");
                printf("1. Beginner\n2. Intermediate\n3. Advanced\n");
                printf("Your choice: ");
                if (scanf("%d", &choice) != 1 || !validate_difficulty(choice)) {
                    while (getchar() != '\n');
                    break;
                }
                level = choice - 1;
                while (getchar() != '\n'); 
                
                printf("\nSelect mode:\n");
                printf("1. Words\n2. Sentences\n3. Texts\n");
                printf("Your choice: ");
                if (scanf("%d", &choice) != 1 || !validate_mode(choice)) {
                    while (getchar() != '\n');
                    break;
                }
                mode = choice - 1;
                while (getchar() != '\n');
                
                const char* text = get_random_text(level, mode);
                TestResult result = run_typing_test(text);
                
                printf("\n=== Test Results ===\n");
                printf("Correct characters: %d\n", result.correct);
                printf("Incorrect characters: %d\n", result.incorrect);
                printf("Time taken: %.2f seconds\n", result.time_taken);
                printf("Typing speed: %.2f chars/min (%.2f WPM)\n", result.speed, result.wpm);
                printf("Accuracy: %.2f%%\n", result.accuracy);
                
                save_result(result);
                add_player_name(&result);
                update_leaderboard(result.player_name, 
                                  result.correct, 
                                  result.wpm, 
                                  result.accuracy);
                break;
                
            case 2:
                printf("\nSelect difficulty:\n");
                printf("1. Beginner\n2. Intermediate\n3. Advanced\n");
                printf("Your choice: ");
                if (scanf("%d", &choice) != 1 || !validate_difficulty(choice)) {
                    while (getchar() != '\n');
                    break;
                }
                level = choice - 1;
                
                printf("\nSelect mode:\n");
                printf("1. Words\n2. Sentences\n3. Texts\n");
                printf("Your choice: ");
                if (scanf("%d", &choice) != 1 || !validate_mode(choice)) {
                    while (getchar() != '\n');
                    break;
                }
                mode = choice - 1;
                
                printf("\nEnter test duration in minutes (1-10): ");
                if (scanf("%d", &test_time) != 1 || !validate_time(test_time)) {
                    while (getchar() != '\n');
                    break;
                }
                
                TestResult timed_result = run_timed_test(level, mode, test_time);
                save_result(timed_result);
                break;
                
            case 3:
                printf("\nSelect starting difficulty:\n");
                printf("1. Beginner\n2. Intermediate\n3. Advanced\n");
                printf("Your choice: ");
                if (scanf("%d", &choice) != 1 || !validate_difficulty(choice)) {
                    while (getchar() != '\n');
                    break;
                }
                level = choice - 1;
                
                TestResult snake_result = run_snake_mode(level);
                save_result(snake_result);
                break;
                
            case 4:
                practice_key_combos();
                break;
                
            case 5:
                print_statistics();
                break;
                
            case 6: 
                show_leaderboard();
                break;

            case 7:
                printf("Goodbye!\n");
                return 0;               
        }
        
        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
        getchar();
    }
    
    return 0;
}
