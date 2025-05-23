#include "train.h"

void search_records(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(1);
    }

    int choice;
    printf("\nSearch by:\n1. Destination\n2. Number\n3. Time\nChoice: ");
    scanf("%d", &choice);
    getchar();

    Train record;
    int found = 0;
    char search_dest[50];
    int search_num, search_hours, search_minutes;

    switch (choice) {
        case 1:
            printf("Destination: ");
            fgets(search_dest, 50, stdin);
            search_dest[strcspn(search_dest, "\n")] = '\0';
            break;
        case 2:
            printf("Enter train's number: ");
            scanf("%d", &search_num);
            getchar();
            break;
        case 3:
            printf("Enter time (hours minutes): ");
            scanf("%d %d", &search_hours, &search_minutes);
            getchar();
            break;
        default:
            printf("Incorrect choice!\n");
            fclose(file);
            return;
    }

    printf("\nResults:\n");
    while (fread(&record, sizeof(Train), 1, file)) {
        int match = 0;
        switch (choice) {
            case 1:
                if (strcmp(record.destination, search_dest) == 0) match = 1;
                break;
            case 2:
                if (record.train_number == search_num) match = 1;
                break;
            case 3:
                if (record.departure_time[0] == search_hours && 
                    record.departure_time[1] == search_minutes) match = 1;
                break;
        }
        if (match) {
            printf("Destination: %s\nNumber: %d\nTime: %02d:%02d\n\n",
                   record.destination,
                   record.train_number,
                   record.departure_time[0],
                   record.departure_time[1]);
            found = 1;
        }
    }

    if (!found) {
        printf("Not found.\n");
    }

    fclose(file);
}