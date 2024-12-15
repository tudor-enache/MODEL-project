// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/naive_multiplication.h"
#include "../include/strassen_multiplication.h"
#include "../include/lu_decomposition.h"
#include "../include/lu_inversion.h"
#include "../include/strassen_inversion.h"

int main() {
    // time inversion for matrix sizes in [65, 512]
    // write timings to a file
    FILE *fp = fopen("data/inv.csv", "w");
    if (fp == NULL) {
        printf("Error opening mult file.\n");
    }

    clock_t start, end;
    double duration;

    // interesting to explain when and why we need to calculate the closest power of 2
    // i.e. when does this need to go into our analysis
    for(int n = 65; n < 129; n++) {
        printf("Computing for: %d.\n", n);
        double** A = allocate_matrix(n, 1);

        start = clock();
        double** I = identity(n);
        lu_inv(A, I, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "LU,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_inv(A, n);
        strassen_inv(P, 128, naive_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SN,%d,%f\n", n, duration);

        start = clock();
        double** Q = pad_inv(A, n);
        strassen_inv(Q, 128, strassen_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SS,%d,%f\n", n, duration);

        printf("Done.\n");
    }
    for(int n = 129; n < 257; n++) {
        printf("Computing for: %d.\n", n);
        double** A = allocate_matrix(n, 1);

        start = clock();
        double** I = identity(n);
        lu_inv(A, I, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "LU,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_inv(A, n);
        strassen_inv(P, 256, naive_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SN,%d,%f\n", n, duration);

        start = clock();
        double** Q = pad_inv(A, n);
        strassen_inv(Q, 256, strassen_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SS,%d,%f\n", n, duration);

        printf("Done.\n");
    }
    for(int n = 257; n < 513; n++) {
        printf("Computing for: %d.\n", n);
        double** A = allocate_matrix(n, 1);

        start = clock();
        double** I = identity(n);
        lu_inv(A, I, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "LU,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_inv(A, n);
        strassen_inv(P, 512, naive_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SN,%d,%f\n", n, duration);

        start = clock();
        double** Q = pad_inv(A, n);
        strassen_inv(Q, 512, strassen_mult);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "SS,%d,%f\n", n, duration);

        printf("Done.\n");
    }

    return 0;
}
