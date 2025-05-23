#ifndef TYPING_TRAINER_H
#define TYPING_TRAINER_H

#define MAX_NAME_LENGTH 50
#define MAX_LEADERS 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    double wpm;
    double accuracy;
} LeaderEntry;

typedef enum {
    LEVEL_BEGINNER,
    LEVEL_INTERMEDIATE,
    LEVEL_ADVANCED
} DifficultyLevel;

typedef enum {
    MODE_WORDS,
    MODE_SENTENCES,
    MODE_TEXTS,
    MODE_KEY_COMBOS
} TrainingMode;

typedef struct {
    int correct;
    int incorrect;
    double time_taken;
    double speed;
    double wpm;
    double accuracy;
    char player_name[MAX_NAME_LENGTH];
} TestResult;

int validate_menu_choice(int choice);
int validate_difficulty(int level);
int validate_mode(int mode);
int validate_time(int time);

TestResult run_typing_test(const char* text);
const char* get_random_text(DifficultyLevel level, TrainingMode mode);
const char* get_key_combo(DifficultyLevel level);
void practice_key_combos();
void print_statistics();
void save_result(TestResult result);
void show_menu();
TestResult run_timed_test(DifficultyLevel level, TrainingMode mode, int minutes);
TestResult run_snake_mode(DifficultyLevel initial_level);

void save_leaderboard(const LeaderEntry* leaders, int count);
void load_leaderboard(LeaderEntry* leaders, int* count);
void update_leaderboard(const char* name, int score, double wpm, double accuracy);
void show_leaderboard();
void add_player_name(TestResult* result);

#endif