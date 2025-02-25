// 1. Формирование матрицы. fillmatrix
// 1*. Ручное заполнение матрицы. inputmatrix
// 2. Нахождение элементов главной и побочной диагонали. sumdiagonal
// 3. Формируем массив В. // int* B = sumdiagonal(matrix, n);
// 4. Мax в исходной. maxvalue
// 5. Пройти по массиву В и определить количетсво элементов меньших максимального. ltmax
// 6. Если таковых нет, то упорядочить по убыванию. Иначе вывести В и количество элемементов. sorting
// *. Вывод матрицы. printmatrix
// **. Чистка памяти. freeMemory

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printmatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void randmatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10 + 1;
        }
    }
}

void inputmatrix(int **matrix, int n) {
    printf("Enter matrix elements: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Element [%d][%d]: ", i, j);
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid input.");
                exit(1); 
            }
        }
    }
}


int* sumdiagonal(int **matrix, int n) {
    int *B = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        B[i] = matrix[i][i] + matrix[i][n - i - 1];
    } 
    return B;
}

int maxvalue(int **matrix, int n) {
    int mv = matrix[0][0];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
           if (matrix[i][j] >= mv){
                mv = matrix[i][j];
           }
        }
    }
    return mv;
}

int ltmax(int *B, int n, int mv){ 
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (B[i] < mv) {
            cnt++;
        }
    }
    return cnt;
}

void sorting(int *B, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++){
            if (B[i] < B[j]){
                int t = B[i];
                B[i] = B[j];
                B[j] = t;
            }
        }
    }
}

void freeMemory(int **matrix, int n, int* B) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(B);
}

int main() {
    int n;
    printf("Enter size of matrix: ");
    scanf("%d", &n);
    if (n <= 1 || n >= 15){
        printf("Invalid matrix size.");
    } else {     

        int **matrix = (int**)malloc(n * sizeof(int*)); // выделяем память для массива указателей
        for (int i = 0; i < n; i++) { // выделение памяти для каждой строки 
            matrix[i] = (int*)malloc(n * sizeof(int));
        }

        int choice = 0;
        printf("Random filling - print <1> \nFill yourself - print <2> \nYour choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            srand(time(NULL));
            randmatrix(matrix, n);
        } else if (choice == 2) {
            inputmatrix(matrix, n);
        } else {
            printf("Incorrect choice.");
            return 0;
        }

        printmatrix(matrix, n);
        int *B = sumdiagonal(matrix, n);
        int mv = maxvalue(matrix, n);
        int cnt = ltmax(B, n, mv);
        
        if (cnt == 0) {
            sorting(B, n);
        } else {
            printf("Count of elements than less max: %d \n", cnt);
        }

        printf("Massive B: \n");

        for (int i = 0; i < n; i++) {
            printf("%d ", B[i]);
        }
        freeMemory(matrix, n, B);
    }
}   
