#include "train.h"

int main() {
    int n;
    printf("Enter number of routes: ");
    scanf("%d", &n);
    getchar();

    add_records("Train.dat", n);
    search_records("Train.dat");

    return 0;
}