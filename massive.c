#include <stdio.h>

int removemorethanav(int *m, int *s, float av) {
    int ns = 0;
    for (int i = 0; i < *s; i++) {
        if (m[i] <= av){
            m[ns++] = m[i];
        }
    }
    *s = ns;
    return ns;
}

int isPerfect(int num) {
    if (num <= 1) return 0;
    int sum = 0;
    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) sum += i;
    }
    return sum == num;
}

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n;
    printf("Enter length of massive: ");
    scanf("%d", &n);
    int m[n];
    int i;
    for (i = 0; i < n; i++) {
        printf("m[%d] = ", i);
        scanf("%d", &m[i]);
    }
    double sum = 0;
    for (i = 0; i < n; i++) {
        sum += m[i];
    }
    float av = sum / n;
    int bprime = 0;
    int bperfect = 0;

    printf("Your massive before: ");
        for (i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }

    for (i = 0; i < n; i++) {
        if (isPrime(m[i])) bprime++;
        if (isPerfect(m[i])) bperfect++;
    }
    printf("\nCount prime: %d \n", bprime);
    printf("Count perfect: %d \n", bperfect);

    removemorethanav(m,&n,av);
    printf("Your massive after: ");
    for (i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }

    int aprime = 0;
    int aperfect = 0;

    for (i = 0; i < n; i++) {
        if (isPrime(m[i])) aprime++;
        if (isPerfect(m[i])) aperfect++;
    }
    printf("\nCount prime: %d \n", aprime);
    printf("Count perfect: %d \n", aperfect);
}