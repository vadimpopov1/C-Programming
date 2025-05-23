#ifndef TRAIN_H
#define TRAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char destination[50];
    int train_number;
    int departure_time[2];
} Train;

void add_records(const char* filename, int n);
void search_records(const char* filename);

#endif
