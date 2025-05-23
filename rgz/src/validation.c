#include "typing_trainer.h"
#include <stdio.h>

int validate_menu_choice(int choice) {
    if (choice < 1 || choice > 7) {
        printf("Invalid choice. Please select option between 1-7.\n");
        return 0;
    }
    return 1;
}

int validate_difficulty(int level) {
    if (level < 1 || level > 3) {
        printf("Invalid difficulty level. Please choose between 1-3.\n");
        return 0;
    }
    return 1;
}

int validate_mode(int mode) {
    if (mode < 1 || mode > 4) {
        printf("Invalid mode. Please choose between 1-4.\n");
        return 0;
    }
    return 1;
}

int validate_time(int time) {
    if (time < 1 || time > 10) {
        printf("Invalid time. Please choose between 1-10 minutes.\n");
        return 0;
    }
    return 1;
}