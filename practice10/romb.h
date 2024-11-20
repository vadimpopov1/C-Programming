#ifndef ROMB_H
#define ROMB_H

#include <stddef.h>

typedef struct {
    float d1;
    float d2;
} Romb;

float area(Romb r);
int is_square(Romb r);

#endif
