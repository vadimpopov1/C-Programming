#include "train.h"

void add_records(const char* filename, int n) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    Train record;
    for (int i = 0; i < n; ++i) {
        printf("\nWrite %d:\n", i + 1);
        
        printf("Destination: ");
        fgets(record.destination, 50, stdin);
        record.destination[strcspn(record.destination, "\n")] = '\0';

        printf("Train's number: ");
        scanf("%d", &record.train_number);
        getchar();

        printf("Time (hours minutes): ");
        scanf("%d %d", &record.departure_time[0], &record.departure_time[1]);
        getchar();

        fwrite(&record, sizeof(Train), 1, file);
    }
    fclose(file);
}