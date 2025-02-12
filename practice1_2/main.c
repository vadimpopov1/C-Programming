#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define N 5
#define showinf 1

void printCPUInfo() {
    printf("CPU Info (macOS):\n");
    system("sysctl -n machdep.cpu.brand_string");
}

struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(const char *name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, sizeof(newStudent.name) - 1);
    newStudent.name[sizeof(newStudent.name) - 1] = '\0';
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printDataSize(int n) {
    size_t size = n * sizeof(struct Student);
    printf("Data size: %zu bytes\n", size);
}

void printStudentInfo(struct Student student) {
    printf("Name: %s, Math: %d, Phy: %d, Inf: %d, Total: %d\n", student.name, student.math, student.phy, student.inf, student.total);
}

void insertionSort(struct Student arr[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].total < key.total) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void countingSort(struct Student arr[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].total > max) {
            max = arr[i].total;
        }
    }

    int* count = (int*)calloc(max + 1, sizeof(int));
    struct Student* output = (struct Student*)malloc(n * sizeof(struct Student));

    for (int i = 0; i < n; i++) {
        count[arr[i].total]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i].total] - 1] = arr[i];
        count[arr[i].total]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Student arr[], int low, int high) {
    int pivot = arr[high].total;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].total > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(struct Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    struct Student students[N];
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, 64, "Student%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }
    if (showinf == 1) {
        printf("Before sorting:\n");
        for (int i = 0; i < N; i++) {
            printStudentInfo(students[i]);
        }
        printf("\n");
    }
    printCPUInfo(); 
    printDataSize(N);

    clock_t startTime, endTime;
    double cpu_time_used;

    startTime = clock();
    insertionSort(students, N);
    endTime = clock();
    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Insertion Sort Time: %f seconds\n", cpu_time_used);

    startTime = clock();
    countingSort(students, N);
    endTime = clock();
    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Counting Sort Time: %f seconds\n", cpu_time_used);

    startTime = clock();
    quickSort(students, 0, N - 1);
    endTime = clock();
    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Quick Sort Time: %f seconds\n", cpu_time_used);
    if (showinf == 1) {
        printf("\n");
        printf("After sorting:\n");
        for (int i = 0; i < N; i++) {
            printStudentInfo(students[i]);
        }
    }
    return 0;
}
