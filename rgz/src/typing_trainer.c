#include "typing_trainer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

static const char* beginner_words[] = {
    "hello", "world", "keyboard", "mouse", "screen", "type", "code", "learn", "skill", "fast",
    "apple", "basic", "color", "dance", "earth", "fruit", "green", "happy", "input", "jump",
    "kite", "light", "music", "night", "open", "piano", "quiet", "river", "sunny", "train",
    "water", "young", "zebra", "chair", "table", "phone", "laptop", "window", "door", "garden"
};
static const int beginner_words_count = sizeof(beginner_words) / sizeof(beginner_words[0]);

static const char* intermediate_words[] = {
    "algorithm", "function", "variable", "pointer", "structure", 
    "compile", "execute", "debug", "syntax", "memory",
    "binary", "cache", "driver", "exception", "framework",
    "garbage", "handler", "iterator", "javascript", "kernel",
    "linked", "macro", "nullable", "overload", "protocol",
    "query", "regex", "stack", "template", "utility"
};
static const int intermediate_words_count = sizeof(intermediate_words) / sizeof(intermediate_words[0]);

static const char* advanced_words[] = {
    "polymorphism", "encapsulation", "inheritance", "multithreading", "asynchronous",
    "dereferencing", "segmentation", "optimization", "parallelism", "recursion",
    "metaprogramming", "reflection", "serialization", "virtualization", "cryptography",
    "blockchain", "concurrency", "distributed", "ephemeral", "idempotent",
    "juxtaposition", "kubernetes", "monad", "nonblocking", "orthogonal",
    "quantum", "reactive", "stochastic", "transpilation", "universal"
};
static const int advanced_words_count = sizeof(advanced_words) / sizeof(advanced_words[0]);

static const char* beginner_sentences[] = {
    "I learn to type quickly.",
    "C is a powerful language.",
    "Practice every day.",
    "Typing speed matters.",
    "Keep your fingers on home row.",
    "The sun is bright today.",
    "I enjoy reading books.",
    "Programming can be fun.",
    "My cat likes to sleep.",
    "We learn new things daily.",
    "Open the window please.",
    "Music helps me focus.",
    "Winter is coming soon.",
    "The sky is blue.",
    "I have two computers."
};
static const int beginner_sentences_count = sizeof(beginner_sentences) / sizeof(beginner_sentences[0]);

static const char* intermediate_sentences[] = {
    "The quick brown fox jumps over the lazy dog.",
    "Programming requires logic and creativity.",
    "Debugging is twice as hard as writing the code.",
    "Always initialize your variables.",
    "Memory management is crucial in C.",
    "Regular expressions can match complex patterns.",
    "Object-oriented programming uses classes and objects.",
    "Version control systems track changes in code.",
    "The stack grows downward in memory.",
    "Pointers store memory addresses.",
    "Sorting algorithms have different time complexities.",
    "Virtual functions enable runtime polymorphism.",
    "Exception handling prevents program crashes.",
    "The heap is used for dynamic memory allocation.",
    "Lambda expressions provide concise syntax."
};
static const int intermediate_sentences_count = sizeof(intermediate_sentences) / sizeof(intermediate_sentences[0]);

static const char* advanced_sentences[] = {
    "The complexity of modern software systems often requires sophisticated design patterns.",
    "Optimizing performance-critical code sections can lead to significant improvements.",
    "Concurrent programming introduces challenges like race conditions and deadlocks.",
    "Understanding pointer arithmetic is essential for low-level programming tasks.",
    "The C standard library provides numerous functions for common programming tasks.",
    "Template metaprogramming in C++ enables compile-time computation.",
    "Lock-free data structures require careful memory ordering considerations.",
    "Distributed systems must handle partial failures and network partitions.",
    "Type inference algorithms determine expressions' types without explicit annotations.",
    "Continuation-passing style transforms recursive functions into tail-recursive form.",
    "Monads in functional programming abstract program-wide concerns like state and I/O.",
    "Just-in-time compilation dynamically optimizes hot code paths at runtime.",
    "Homomorphic encryption allows computation on encrypted data without decryption.",
    "The actor model provides high-level abstractions for concurrent computation.",
    "Quantum algorithms like Shor's can factor integers exponentially faster than classical ones."
};
static const int advanced_sentences_count = sizeof(advanced_sentences) / sizeof(advanced_sentences[0]);

static const char* special_words[] = {
    "12345", "!@#$%", "3.1415", "0xFFFF", "var_name",
    "camelCase", "snake_case", "PascalCase", "UPPER", "lower",
    "a1b2c3", "test123", "end\n", "tab\t", "space "
};
static const int special_words_count = sizeof(special_words) / sizeof(special_words[0]);

static const char* pangrams[] = {
    "Pack my box with five dozen liquor jugs.",
    "How vexingly quick daft zebras jump!",
    "Bright vixens jump; dozy fowl quack.",
    "Sphinx of black quartz, judge my vow.",
    "Waltz, bad nymph, for quick jigs vex."
};
static const int pangrams_count = sizeof(pangrams) / sizeof(pangrams[0]);

static const char* code_snippets[] = {
    "for(int i=0; i<10; i++) { printf(\"%d\\n\", i); }",
    "int main() { return 0; }",
    "#define MAX(a,b) ((a)>(b)?(a):(b))",
    "typedef struct { int x; int y; } Point;",
    "void swap(int *a, int *b) { int t=*a; *a=*b; *b=t; }"
};
static const int code_snippets_count = sizeof(code_snippets) / sizeof(code_snippets[0]);

static const char* beginner_combos[] = {
    "asdf", "jkl;", "fdsa", ";lkj",
    "a s d f", "j k l ;", "qwer", "uiop"
};
static const int beginner_combos_count = sizeof(beginner_combos) / sizeof(beginner_combos[0]);

static const char* intermediate_combos[] = {
    "asdf jkl;", "fdsa ;lkj", "qwer uiop",
    "asdfg", "hjkl;", "gfdsa", ";lkjh",
    "aqsw", "de fr", "gt hy", "ju ki", "lo p;"
};
static const int intermediate_combos_count = sizeof(intermediate_combos) / sizeof(intermediate_combos[0]);

static const char* advanced_combos[] = {
    "asdfg hjkl;", "gfdsa ;lkjh", "aqsw defr",
    "qaz wsx edc rfv tgb yhn ujm ik, ol. p;/",
    "1qaz 2wsx 3edc 4rfv 5tgb 6yhn 7ujm 8ik, 9ol. 0p;/",
    "!QAZ @WSX #EDC $RFV TGB ^YHN &UJM *IK< (OL> )P:?"
};
static const int advanced_combos_count = sizeof(advanced_combos) / sizeof(advanced_combos[0]);

static TestResult statistics[100];
static int stats_count = 0;

const char* get_key_combo(DifficultyLevel level) {
    switch (level) {
        case LEVEL_BEGINNER: 
            return beginner_combos[rand() % beginner_combos_count];
        case LEVEL_INTERMEDIATE:
            return intermediate_combos[rand() % intermediate_combos_count];
        case LEVEL_ADVANCED:
            return advanced_combos[rand() % advanced_combos_count];
        default:
            return beginner_combos[0];
    }
}

void practice_key_combos() {
    DifficultyLevel level;
    int choice;
    int round = 1;
    const int max_rounds = 10;
    
    printf("\n=== Key Combinations Practice ===\n");
    printf("Select difficulty:\n");
    printf("1. Beginner (simple combos)\n");
    printf("2. Intermediate (common patterns)\n");
    printf("3. Advanced (full keyboard)\n");
    printf("Your choice: ");
    
    if (scanf("%d", &choice) != 1 || !validate_difficulty(choice)) {
        while (getchar() != '\n');
        return;
    }
    level = choice - 1;
    while (getchar() != '\n');
    
    printf("\nPractice these key combinations. Type each combo and press Enter.\n");
    printf("After %d rounds or if you type 'exit', practice will end.\n\n", max_rounds);
    
    while (round <= max_rounds) {
        const char* combo = get_key_combo(level);
        printf("Round %d/%d\n", round, max_rounds);
        printf("Type: %s\n", combo);
        printf("Your input (or 'exit' to finish): ");
        
        char input[256];
        if (!fgets(input, sizeof(input), stdin)) {
            break; 
        }
        
        input[strcspn(input, "\n")] = '\0'; 
        
        if (strcmp(input, "exit") == 0) {
            printf("\nPractice session ended by user.\n");
            break;
        }
        
        int correct = 1;
        int min_len = strlen(combo) < strlen(input) ? strlen(combo) : strlen(input);
        
        for (int i = 0; i < min_len; i++) {
            if (combo[i] != input[i]) {
                printf("\033[1;31m%c\033[0m", input[i]); 
                correct = 0;
            }
        }
        
        if (strlen(input) != strlen(combo)) {
            correct = 0;
            if (strlen(input) < strlen(combo)) {
                printf("\033[1;31m...\033[0m");
            }
        }
        
        if (correct) {
            printf("\033[1;32mPerfect! Well done!\033[0m\n\n");
        } else {
            printf("\033[1;31mMistakes detected. Try again!\033[0m\n");
            printf("Correct combo: %s\n\n", combo);
        }
        
        round++;
    }
    
    printf("\nKey combination practice completed!\n");
    printf("Press Enter to return to main menu...");
    while (getchar() != '\n');
}

static double calculate_wpm(int correct_chars, double time_seconds) {
    if (time_seconds <= 0) return 0.0;
    return (correct_chars / 5.0) / (time_seconds / 60.0);
}

TestResult run_typing_test(const char* text) {
    TestResult result = {0};
    if (!text || strlen(text) == 0) {
        fprintf(stderr, "Error: Empty text provided for typing test\n");
        return result;
    }

    int target_len = strlen(text);
    printf("\nType the following text:\n%s\n", text);
    printf("Press Enter to start typing...\n");
    while (getchar() != '\n');

    time_t start_time = time(NULL);
    
    printf("Start typing now:\n");
    char* input = malloc(target_len * 2 + 1);
    if (!input) {
        fprintf(stderr, "Memory allocation error\n");
        return result;
    }
    
    if (!fgets(input, target_len * 2, stdin)) {
        free(input);
        fprintf(stderr, "Error reading input\n");
        return result;
    }
    
    time_t end_time = time(NULL);
    result.time_taken = difftime(end_time, start_time);
    
    input[strcspn(input, "\n")] = '\0';
    
    int min_len = target_len < strlen(input) ? target_len : strlen(input);
    
    for (int i = 0; i < min_len; i++) {
        if (text[i] == input[i]) {
            result.correct++;
        } else {
            result.incorrect++;
            printf("\033[1;31m%c\033[0m", input[i]);
        }
    }
    printf("\n");
    
    int input_len = strlen(input);
    if (target_len > input_len) {
        result.incorrect += target_len - input_len;
    } else if (input_len > target_len) {
        result.incorrect += input_len - target_len;
    }
    
    if (result.time_taken > 0) {
        result.speed = (result.correct / result.time_taken) * 60;
        result.wpm = calculate_wpm(result.correct, result.time_taken);
    }
    
    if (result.correct + result.incorrect > 0) {
        result.accuracy = ((double)result.correct / (result.correct + result.incorrect)) * 100;
    }
    
    free(input);
    
    return result;
}

const char* get_random_text(DifficultyLevel level, TrainingMode mode) {
    static unsigned int seed_initialized = 0;
    if (!seed_initialized) {
        srand(time(NULL));
        seed_initialized = 1;
    }

    if (mode == MODE_WORDS) {
        switch (level) {
            case LEVEL_BEGINNER: 
                return beginner_words[rand() % beginner_words_count];
            case LEVEL_INTERMEDIATE:
                return intermediate_words[rand() % intermediate_words_count];
            case LEVEL_ADVANCED:
                return advanced_words[rand() % advanced_words_count];
            default:
                return beginner_words[0];
        }
    } else if (mode == MODE_SENTENCES) {
        switch (level) {
            case LEVEL_BEGINNER: 
                return beginner_sentences[rand() % beginner_sentences_count];
            case LEVEL_INTERMEDIATE:
                return intermediate_sentences[rand() % intermediate_sentences_count];
            case LEVEL_ADVANCED:
                return advanced_sentences[rand() % advanced_sentences_count];
            default:
                return beginner_sentences[0];
        }
    } else if (mode == MODE_TEXTS) {
        static char combined_text[512];
        int sentences_to_combine = 3 + level;
        
        combined_text[0] = '\0';
        for (int i = 0; i < sentences_to_combine; i++) {
            const char* sentence = get_random_text(level, MODE_SENTENCES);
            strcat(combined_text, sentence);
            strcat(combined_text, " ");
        }
        return combined_text;
    } else if (mode == MODE_KEY_COMBOS) {
        return get_key_combo(level);
    }
    
    return beginner_sentences[0];
}

void print_statistics() {
    if (stats_count == 0) {
        printf("No statistics available yet.\n");
        return;
    }

    double total_speed = 0, total_accuracy = 0, total_wpm = 0;
    int best_speed = 0, best_wpm = 0;
    double best_accuracy = 0;

    printf("\n=== Typing Statistics ===\n");
    printf("%-5s %-8s %-8s %-8s %-8s %-8s\n", 
           "Test", "Correct", "Errors", "Time", "Speed", "Accuracy");
    
    for (int i = 0; i < stats_count; i++) {
        TestResult r = statistics[i];
        printf("%-5d %-8d %-8d %-8.1f %-8.1f %-8.1f%%\n", 
               i+1, r.correct, r.incorrect, r.time_taken, r.speed, r.accuracy);

        total_speed += r.speed;
        total_accuracy += r.accuracy;
        total_wpm += r.wpm;

        if (r.speed > best_speed) best_speed = r.speed;
        if (r.wpm > best_wpm) best_wpm = r.wpm;
        if (r.accuracy > best_accuracy) best_accuracy = r.accuracy;
    }

    printf("\n=== Summary ===\n");
    printf("Average speed: %.1f chars/min\n", total_speed / stats_count);
    printf("Average WPM: %.1f words/min\n", total_wpm / stats_count);
    printf("Average accuracy: %.1f%%\n", total_accuracy / stats_count);
    printf("Best speed: %d chars/min\n", best_speed);
    printf("Best WPM: %d words/min\n", best_wpm);
    printf("Best accuracy: %.1f%%\n", best_accuracy);
}

void save_result(TestResult result) {
    if (stats_count < 100) {
        statistics[stats_count++] = result;
    } else {
        for (int i = 0; i < 99; i++) {
            statistics[i] = statistics[i+1];
        }
        statistics[99] = result;
    }
}

void save_leaderboard(const LeaderEntry* leaders, int count) {
    FILE* file = fopen("leaderboard.bin", "wb");
    if (!file) return;
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(leaders, sizeof(LeaderEntry), count, file);
    
    fclose(file);
}

void load_leaderboard(LeaderEntry* leaders, int* count) {
    FILE* file = fopen("leaderboard.bin", "rb");
    if (!file) {
        *count = 0;
        return;
    }
    
    fread(count, sizeof(int), 1, file);
    fread(leaders, sizeof(LeaderEntry), *count, file);
    
    fclose(file);
}

void update_leaderboard(const char* name, int score, double wpm, double accuracy) {
    LeaderEntry leaders[MAX_LEADERS];
    int count = 0;
    
    load_leaderboard(leaders, &count);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(leaders[i].name, name) == 0) {
            if (score > leaders[i].score) {
                leaders[i].score = score;
                leaders[i].wpm = wpm;
                leaders[i].accuracy = accuracy;
            }
            found = true;
            break;
        }
    }
    
    if (!found) {
        if (count < MAX_LEADERS) {
            strncpy(leaders[count].name, name, MAX_NAME_LENGTH);
            leaders[count].score = score;
            leaders[count].wpm = wpm;
            leaders[count].accuracy = accuracy;
            count++;
        } else {
            int min_index = 0;
            for (int i = 1; i < count; i++) {
                if (leaders[i].score < leaders[min_index].score) {
                    min_index = i;
                }
            }
            
            if (score > leaders[min_index].score) {
                strncpy(leaders[min_index].name, name, MAX_NAME_LENGTH);
                leaders[min_index].score = score;
                leaders[min_index].wpm = wpm;
                leaders[min_index].accuracy = accuracy;
            }
        }
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (leaders[i].score < leaders[j].score) {
                LeaderEntry temp = leaders[i];
                leaders[i] = leaders[j];
                leaders[j] = temp;
            }
        }
    }
    
    save_leaderboard(leaders, count);
}

void show_leaderboard() {
    LeaderEntry leaders[MAX_LEADERS];
    int count = 0;
    
    load_leaderboard(leaders, &count);
    
    printf("\n=== LEADERBOARD ===\n");
    printf("%-3s %-20s %-10s %-10s %-10s\n", "#", "Name", "Score", "WPM", "Accuracy");
    
    for (int i = 0; i < count; i++) {
        printf("%-3d %-20s %-10d %-10.1f %-10.1f%%\n", 
               i + 1, 
               leaders[i].name, 
               leaders[i].score,
               leaders[i].wpm,
               leaders[i].accuracy);
    }
    
    if (count == 0) {
        printf("No records yet. Be the first!\n");
    }
}

void add_player_name(TestResult* result) {
    printf("\nEnter your name (max %d chars): ", MAX_NAME_LENGTH - 1);
    fgets(result->player_name, MAX_NAME_LENGTH, stdin);
    result->player_name[strcspn(result->player_name, "\n")] = '\0';
}

TestResult run_timed_test(DifficultyLevel level, TrainingMode mode, int minutes) {
    TestResult final_result = {0};
    time_t end_time = time(NULL) + minutes * 60;
    int rounds = 0;

    printf("\nTimed test started! You have %d minutes.\n", minutes);
    printf("Type as much as you can. Results will be shown when time is up.\n");
    
    while (getchar() != '\n');

    while (time(NULL) < end_time) {
        const char* text = get_random_text(level, mode);
        printf("\nText %d:\n%s\n", ++rounds, text);
        
        time_t round_start = time(NULL);
        char input[512];
        
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        if (strchr(input, '\n') == NULL) {
            while (getchar() != '\n');
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        int min_len = strlen(text) < strlen(input) ? strlen(text) : strlen(input);
        
        for (int i = 0; i < min_len; i++) {
            if (text[i] == input[i]) {
                final_result.correct++;
            } else {
                final_result.incorrect++;
            }
        }
        
        int text_len = strlen(text);
        int input_len = strlen(input);
        if (text_len > input_len) {
            final_result.incorrect += text_len - input_len;
        } else {
            final_result.incorrect += input_len - text_len;
        }
    }
    
    final_result.time_taken = minutes * 60.0;
    if (final_result.time_taken > 0) {
        final_result.speed = (final_result.correct / final_result.time_taken) * 60;
        final_result.wpm = calculate_wpm(final_result.correct, final_result.time_taken);
    }
    
    if (final_result.correct + final_result.incorrect > 0) {
        final_result.accuracy = ((double)final_result.correct / (final_result.correct + final_result.incorrect)) * 100;
    }
    
    printf("\n=== Time's up! Final Results ===\n");
    printf("Rounds completed: %d\n", rounds);
    printf("Total correct characters: %d\n", final_result.correct);
    printf("Total incorrect characters: %d\n", final_result.incorrect);
    printf("Typing speed: %.1f chars/min (%.1f WPM)\n", final_result.speed, final_result.wpm);
    printf("Accuracy: %.1f%%\n", final_result.accuracy);

    add_player_name(&final_result);
    update_leaderboard(final_result.player_name, 
                      final_result.correct, 
                      final_result.wpm, 
                      final_result.accuracy);
    
    return final_result;
}

TestResult run_snake_mode(DifficultyLevel initial_level) {
    TestResult final_result = {0};
    DifficultyLevel current_level = initial_level;
    int score = 0, round = 1, total_rounds = 0;
    time_t start_time = time(NULL);
    double total_accuracy = 0;
    
    printf("\n=== Snake Mode ===\n");
    printf("Type correctly to level up! Need 90%% accuracy to advance.\n");
    
    while (getchar() != '\n');

    while (1) {
        const char* text = get_random_text(current_level, MODE_SENTENCES);
        printf("\nRound %d | Level: %d | Score: %d\n", 
               round, current_level + 1, score);
        printf("Text: %s\n", text);
        
        time_t round_start = time(NULL);
        char input[512];
        
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        
        if (strchr(input, '\n') == NULL) {
            while (getchar() != '\n');
        }
        
        input[strcspn(input, "\n")] = '\0';
        
        TestResult round_result = {0};
        int min_len = strlen(text) < strlen(input) ? strlen(text) : strlen(input);
        
        for (int i = 0; i < min_len; i++) {
            if (text[i] == input[i]) {
                round_result.correct++;
            } else {
                round_result.incorrect++;
                printf("\033[1;31m%c\033[0m", input[i]);
            }
        }
        printf("\n");
        
        int text_len = strlen(text);
        int input_len = strlen(input);
        if (text_len > input_len) {
            round_result.incorrect += text_len - input_len;
        } else {
            round_result.incorrect += input_len - text_len;
        }
        
        round_result.time_taken = difftime(time(NULL), round_start);
        total_rounds++;
        
        double accuracy = (round_result.correct + round_result.incorrect) > 0 ?
            ((double)round_result.correct / (round_result.correct + round_result.incorrect)) * 100 : 0;
        total_accuracy += accuracy;
        
        if (accuracy >= 90.0) {
            score += round_result.correct;
            final_result.correct += round_result.correct;
            final_result.incorrect += round_result.incorrect;
            
            if (current_level < LEVEL_ADVANCED) {
                current_level++;
                printf("Good job! Level increased to %d\n", current_level + 1);
            } else {
                printf("Perfect! Keep going at maximum level!\n");
            }
            round++;
        } else {
            printf("Accuracy %.1f%% is too low. Game over!\n", accuracy);
            break;
        }
    }
    
    final_result.time_taken = difftime(time(NULL), start_time);
    if (final_result.time_taken > 0) {
        final_result.speed = (final_result.correct / final_result.time_taken) * 60;
        final_result.wpm = calculate_wpm(final_result.correct, final_result.time_taken);
    }
    
    if (final_result.correct + final_result.incorrect > 0) {
        final_result.accuracy = ((double)final_result.correct / (final_result.correct + final_result.incorrect)) * 100;
    }
    
    printf("\n=== Final Results ===\n");
    printf("Rounds completed: %d\n", total_rounds);
    printf("Successful rounds: %d\n", round - 1);
    printf("Final level: %d\n", current_level + 1);
    printf("Total score: %d\n", score);
    printf("Correct characters: %d\n", final_result.correct);
    printf("Incorrect characters: %d\n", final_result.incorrect);
    printf("Time taken: %.1f seconds\n", final_result.time_taken);
    printf("Typing speed: %.1f chars/min (%.1f WPM)\n", final_result.speed, final_result.wpm);
    printf("Final accuracy: %.1f%%\n", final_result.accuracy);
    printf("Average accuracy: %.1f%%\n", total_accuracy / total_rounds);

    add_player_name(&final_result);
    update_leaderboard(final_result.player_name, 
                      score,
                      final_result.wpm, 
                      final_result.accuracy);
    
    return final_result;
}

void show_menu() {
    printf("\n=== Typing Trainer ===\n");
    printf("1. Standard Test\n");
    printf("2. Timed Test\n");
    printf("3. Snake Mode\n");
    printf("4. Practice Key Combinations\n");
    printf("5. View Statistics\n");
    printf("6. View Leaderboard\n");
    printf("7. Exit\n");
    printf("Choose an option: ");
}