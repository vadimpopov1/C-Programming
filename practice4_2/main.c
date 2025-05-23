#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Создать текстовый файл с произвольным числом строк. 
// Заменить самое длинное слово каждой строки на ваше имя.

#define MAX_LINE_LENGTH 100

void replace(char *line) {
    char longest[MAX_LINE_LENGTH];
    char cur[MAX_LINE_LENGTH];
    int max_len = 0;
    int cur_len = 0;

    int i = 0;
    while (line[i] != '\0') { // поиск самого длинного слова
        if (isalpha(line[i])) { 
            cur[cur_len++] = line[i];
        } else {
            cur[cur_len] = '\0';
            if (cur_len > max_len) {
                max_len = cur_len;
                strcpy(longest, cur);
            }
            cur_len = 0;
        }
        i++;
    }

    if (cur_len > max_len) {  // проверка на конец строки
        cur[cur_len] = '\0';
        strcpy(longest, cur);
        max_len = cur_len;
    }

    if (max_len > 0) { // замена самого длинного слова + сдвиги
        char *pos = strstr(line, longest); // вхождение лайна в лонгест
        if (pos) {
            memmove(pos + 5, pos + max_len, strlen(pos + max_len) + 1);
            strncpy(pos, "VADIM", 5);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];

    if (argc != 2) { // Проверка на наличие требуемых аргументов
        printf("Use: %s <file>.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r"); // открываем файл вводимый при запуске программы
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // исключаем символ конца строки
        replace(line);
        printf("%s\n", line);
    }

    fclose(file);
}

// gcc -Wall -o main main.c
// ./main <file.txt>
