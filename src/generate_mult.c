#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/lu_decomposition.h"
#include "../include/lu_inversion.h"
#include "../include/naive_multiplication.h"
#include "../include/strassen_inversion.h"
#include "../include/strassen_multiplication.h"

int main() {
    // time multiplication for matrix sizes in [65, 512]
    // write timings to a file
    // will be plotted later using python
    FILE *fp = fopen("data/mult.csv", "w");
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
        double** B = allocate_matrix(n, 1);
        double** result = allocate_matrix(n, 0);
        double** result_p = allocate_matrix(128, 0);

        start = clock();
        naive_mult(A, B, result, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "N,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_upper(A, n);
        double** Q = pad_upper(B, n);
        strassen_mult(P, Q, result_p, 128);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "S,%d,%f\n", n, duration);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(result, n);
        printf("Done.\n");
    }
    for(int n = 129; n < 257; n++) {
        printf("Computing for: %d.\n", n);
        double** A = allocate_matrix(n, 1);
        double** B = allocate_matrix(n, 1);
        double** result = allocate_matrix(n, 0);
        double** result_p = allocate_matrix(256, 0);

        start = clock();
        naive_mult(A, B, result, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "N,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_upper(A, n);
        double** Q = pad_upper(B, n);
        strassen_mult(P, Q, result_p, 256);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "S,%d,%f\n", n, duration);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(result, n);
        printf("Done.\n");
    }
    for(int n = 257; n < 513; n++) {
        printf("Computing for: %d.\n", n);
        double** A = allocate_matrix(n, 1);
        double** B = allocate_matrix(n, 1);
        double** result = allocate_matrix(n, 0);
        double** result_p = allocate_matrix(512, 0);

        start = clock();
        naive_mult(A, B, result, n);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "N,%d,%f\n", n, duration);

        start = clock();
        double** P = pad_upper(A, n);
        double** Q = pad_upper(B, n);
        strassen_mult(P, Q, result_p, 512);
        end = clock();
        duration = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(fp, "S,%d,%f\n", n, duration);

        free_matrix(A, n);
        free_matrix(B, n);
        free_matrix(result, n);
        printf("Done.\n");
    }

    return 0;
}
