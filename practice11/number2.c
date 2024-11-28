#include <stdio.h>  
  
typedef struct  
{  
    char str[5];    // Недостаточно для вывода 4-х значного числа + 1 для терминала. Переполнение буфера.
    int num;  
} NumberRepr;  
  
void format(NumberRepr* number)  
{      
    sprintf(number->str, "%4d", number->num);  // Исправление формата.
}   
int main()  
{  
    NumberRepr number = { .num = 1025 };  
    format(&number);  
    printf("str: %s\n", number.str);      
    printf("num: %d\n", number.num);  
    return 0;  
}  
