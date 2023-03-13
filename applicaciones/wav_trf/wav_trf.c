#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define f 2   // Filter length

double sq2=sqrt(2.0);

void dwt(double *x, int N) {
    double g[f]={sq2,-sq2};       // Haar wavelet filter
    double h[f]={sq2, sq2};       // Haar scaling function
    double *tmp = malloc(sizeof(double) * N);
    int i, j, k;
    int len2 = N / 2;

    for (i = 0; i < len2; i++) {
        tmp[i] = 0.0;
        for (j = 0; j < f; j++) {
            k = (i * 2) + j;
            tmp[i] += h[j] * x[k % N];
            tmp[i + len2] += g[j] * x[k % N];
        }
    }

    for (i = 0; i < N; i++) {
        x[i] = tmp[i];
    }

    free(tmp);
}

int main() {
    double x[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int N = sizeof(x) / sizeof(double);

    int count = 0;
    while (N > 1) {
        printf("Level %d: ", count++);
        dwt(x, N);
        for (int i = 0; i < N; i++) {
            printf("%lf ", x[i]);
        }
        printf("\n");
        N /= 2;
    }

    return 0;
}

~
