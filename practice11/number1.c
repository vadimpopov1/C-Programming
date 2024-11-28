#include <stdio.h>  
#include <stdlib.h>  
  
void init(int** arr, int n)  // Исправлено на указатель на указатель
{  
    *arr = malloc(n * sizeof(int)); // Исправлено на указатель
    int i;  
    for (i = 0; i < n; ++i) {  
            (*arr)[i] = i;  // Исправлено на указатель
        }  
}   

int main()  
    {      
    int* arr = NULL;      
    int n = 10;      
    init(&arr, n);  
    int i;  
    for (i = 0; i < n; ++i) {  
        printf("%d\n", arr[i]); // Приходил NULL, исправил в строке 17 чтобы был указатель на arr.
    }      
    return 0; 
} 
