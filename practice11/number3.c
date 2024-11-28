#include <stdio.h>  
  
#define SQR(x) (x) * (x) // Не вычисляло квадрат

int main() {      
    int y = 5;      
    int z = SQR(y + 1);      
    printf("z = %d\n", z);      
    return 0;
}  
