// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/naive_multiplication.h"
#include "../include/strassen_multiplication.h"

int main() {
    // test correctness of multiplication algorithms
    double** A = allocate_matrix(4, 1);
    double** B = allocate_matrix(4, 1);
    double** result = allocate_matrix(4, 0);

    printf("Testing correctness of multiplication algorithms for matrices:\n");
    print_matrix(A, 4);
    printf("\n");
    print_matrix(B, 4);
    printf("\n");

    naive_mult(A, B, result, 4);
    printf("Naive multiplication:\n");
    print_matrix(result, 4);
    printf("\n");

    strassen_mult(A, B, result, 4);
    printf("Strassen multiplication:\n");
    print_matrix(result, 4);
    printf("\n");

    free_matrix(A, 4);
    free_matrix(B, 4);
    free_matrix(result, 4);

    // time multiplication for matrix sizes in [65, 512]
    // write timings to a file
    // will be plotted later using python
    int generate = 0;

    if (generate == 1) {
        FILE *fp = fopen("data/mult.csv", "w");
        if (fp == NULL) {
            printf("Error opening mult file.\n");
        }

        clock_t start, end;
        double duration;

        for (int n = 65; n < 129; n++) {
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
            double** P = pad_mult(A, n);
            double** Q = pad_mult(B, n);
            strassen_mult(P, Q, result_p, 128);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "S,%d,%f\n", n, duration);

            printf("Done.\n");
        }
        for (int n = 129; n < 257; n++) {
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
            double** P = pad_mult(A, n);
            double** Q = pad_mult(B, n);
            strassen_mult(P, Q, result_p, 256);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "S,%d,%f\n", n, duration);

            printf("Done.\n");
        }
        int n = 512;
        for (int i = 0; i < 3; i++) {
            printf("Computing for: %d.\n", n);
            double** A = allocate_matrix(n, 1);
            double** B = allocate_matrix(n, 1);
            double** result = allocate_matrix(n, 0);

            start = clock();
            naive_mult(A, B, result, n);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "N,%d,%f\n", n, duration);

            start = clock();
            strassen_mult(A, B, result, n);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "S,%d,%f\n", n, duration);

            printf("Done.\n");
            n = n * 2;
        }
    }

    return 0;
}
