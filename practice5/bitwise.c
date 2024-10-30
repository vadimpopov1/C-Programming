#include <stdio.h>

int fzero(int a) {
    int pos = 0;
    while ((a & 1) != 0){ 
        a >>= 1;
        pos++;
    }
    return pos;
} 

int fone(int a) {
    int pos = 0;
    while ((a & 1) != 1){ 
        a >>= 1;
        pos++;
    }
    return pos;
} 

int shift(unsigned int a, unsigned int k) {
    unsigned int size = sizeof(int);
    k %= size;
    unsigned int r_shift = a >> k;
    unsigned int l_shift = a << (size - k);
    return r_shift | l_shift;
}

int main() {
    unsigned int a;
    printf("Input a: ");
    scanf("%u", &a);
    unsigned int k;
    printf("Input k: ");
    scanf("%u", &k);
    int fzero_bit = fzero(a);
    int fone_bit = fone(a)/2;
    unsigned int shift_bit = shift(a,k);
    printf("Last zero bit: %d \n", fzero_bit + 1);
    printf("Last one bit: %d \n", fone_bit + 1);
    printf("Shifted: %d \n", shift_bit);
}
