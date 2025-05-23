#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5

int A[N][N];
int B[N][N];
int C[N][N];

void cleanup_handler(void* arg);
void* thread(void* _);
void* thread_func(void* arg);
void* sleepsort_thread(void* arg);

typedef struct {
    char** strings;
    int count;
} ThreadParams;

typedef struct {
    int start_row;
    int end_row;
} MatrixParams;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int turn = 0;

void cleanup_handler(void* arg) {
    puts("Thread cancelled");
    (void)arg; // явно указываем, что параметр не используется
}

void* thread(void* _) {
    (void)_; // явно указываем, что параметр не используется
    for (int i = 0; i < N; i++) {
        printf("thread: i=%d\n", i);
        sleep(2);
    }
    return NULL;
}

void* thread_func(void* arg) {
    pthread_cleanup_push(cleanup_handler, NULL);
    
    ThreadParams* params = (ThreadParams*)arg;
    for (int i = 0; i < params->count; i++) {
        pthread_testcancel();
        printf("%s\n", params->strings[i]);
        sleep(2);
    }
    
    pthread_cleanup_pop(0);
    return NULL;
}

void* sleepsort_thread(void* arg) {
    int value = *(int*)arg;
    sleep(value);
    printf("%d ", value);
    return NULL;
}

void* child_thread(void* arg) {
    for (int i = 0; i < N; i++) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_mutex_unlock(&mutex);
            usleep(100); 
            pthread_mutex_lock(&mutex);
        }
        printf("Child thread: line %d\n", i);
        turn = 0; 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void print_matrix(int n, int A[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d  ", A[i][j]);
        }
        printf("\n");
    } 
}

void* solve_matrix(void* data) {
    MatrixParams *data2 = (MatrixParams *)data;
    for (int i = data2->start_row; i < data2->end_row; i++) { //  строка
        for (int j = 0; j < N; j++) { // столбцы
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum = sum + A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    free(data2);
    return 0;
}

// int main(void) {
//     pthread_t tid;
//     pthread_create(&tid, NULL, thread, NULL);
//     for (int i = 0; i < N; i++) {
//         printf("Main thread: %d\n", i);
//         sleep(1);
//     }
//     pthread_join(tid, NULL);

//     pthread_create(&tid, NULL, thread, NULL);
//     pthread_join(tid, NULL);
//     for (int i = 0; i < N; i++) {
//         printf("Main after join: %d\n", i);
//     }

//     pthread_t threads[4];
//     ThreadParams params[4];

//     char* strings0[] = {"Thread 1: Line 1", "Thread 1: Line 2", "Thread 1: Line 3"};
//     char* strings1[] = {"Thread 2: Line 1", "Thread 2: Line 2"};
//     char* strings2[] = {"Thread 3: Line 1", "Thread 3: Line 2", "Thread 3: Line 3", "Thread 3: Line 4"};
//     char* strings3[] = {"Thread 4: Line 1"};

//     params[0].strings = strings0; params[0].count = 3;
//     params[1].strings = strings1; params[1].count = 2;
//     params[2].strings = strings2; params[2].count = 4;
//     params[3].strings = strings3; params[3].count = 1;

//     for (int i = 0; i < 4; i++) {
//         pthread_create(&threads[i], NULL, thread_func, &params[i]);
//     }

//     for (int i = 0; i < 4; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     for (int i = 0; i < 4; i++) {
//         pthread_create(&threads[i], NULL, thread_func, &params[i]);
//     }

//     sleep(2);
//     for (int i = 0; i < 4; i++) {
//         pthread_cancel(threads[i]);
//     }

//     sleep(1);
    
//     int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
//     int size = sizeof(arr)/sizeof(arr[0]);
//     pthread_t sleep_threads[size];

//     printf("Original array: ");
//     for (int i = 0; i < size; i++) printf("%d ", arr[i]);
//     printf("\n");

//     printf("Sorted array: ");
//     for (int i = 0; i < size; i++) {
//         pthread_create(&sleep_threads[i], NULL, sleepsort_thread, &arr[i]);
//     }

//     for (int i = 0; i < size; i++) {
//         pthread_join(sleep_threads[i], NULL);
//     }
//     printf("\n");

//     pthread_create(&tid, NULL, child_thread, NULL);

//     for (int i = 0; i < N; i++) {
//         pthread_mutex_lock(&mutex);
//         while (turn != 0) { 
//             pthread_mutex_unlock(&mutex);
//             usleep(100);
//             pthread_mutex_lock(&mutex);
//         }
//         printf("Main thread: line %d\n", i);
//         turn = 1; 
//         pthread_mutex_unlock(&mutex);
//     }

//     pthread_join(tid, NULL);
//     return 0;
// }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Using: %s <number_threads>\n", argv[0]);
        exit(1);
    }
    int number_threads = atoi(argv[1]);
    if (number_threads <= 0 || number_threads > N) {
        fprintf(stderr, "Invalid number of threads. Must be between 1 and %d\n", N);
        exit(2);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }
    printf("Matrix A: \n\n");
    print_matrix(N , A);
    printf("\n");
    printf("Matrix B: \n\n");
    print_matrix(N , B);
    printf("\n");
    pthread_t threads[number_threads];
    int numbers_rows = N / number_threads;

    for (int i = 0; i < number_threads; i++) {  
        MatrixParams* data = malloc(sizeof(MatrixParams));
        data->start_row = i * numbers_rows;
        data->end_row = (i == number_threads - 1) ? N : data->start_row + numbers_rows;
        pthread_create(&threads[i], NULL, solve_matrix, data);
    }

    for (int i = 0; i < number_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix C: \n\n");
    print_matrix(N, C);
    return 0;
}
