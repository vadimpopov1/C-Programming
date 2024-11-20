#include "romb.h"

float area(Romb r) {
    return (r.d1 * r.d2) / 2.0f;
}

int is_square(Romb r) {
    return r.d1 == r.d2;
}
