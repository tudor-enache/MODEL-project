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
    // test correctness of inversion algorithms
    printf("Test correctness of inversion algorithms.\n");
    double** A = allocate_matrix(4, 1); // matrix is generated randomly
    print_matrix(A, 4);

    double** I = identity(4); // generate L matrix for the LU decomposition; initialized to the identity
    double** A_inv = lu_inv(A, I, 4);
    printf("Inverse using the LU decomposition:\n");
    print_matrix(A_inv, 4);
    free_matrix(A_inv, 4);
    printf("\n");

    A_inv = strassen_inv(A, 4, naive_mult); // compute inverse using naive multiplication
    printf("Strassen inverse using naive multiplication:\n");
    print_matrix(A_inv, 4);
    free_matrix(A_inv, 4);
    printf("\n");

    A_inv = strassen_inv(A, 4, strassen_mult); // compute inverse using Strassen multiplication
    printf("Strassen inverse using Strassen multiplication:\n");
    print_matrix(A_inv, 4);
    free_matrix(A_inv, 4);
    printf("\n");

    free_matrix(A, 4);
    free_matrix(I, 4);

    // time inversion for matrix sizes in [65, 512]
    // write timings to a file
    int generate = 0;

    if (generate == 1) {
        FILE *fp = fopen("data/inv.csv", "w");
        if (fp == NULL) {
            printf("Error opening mult file.\n");
        }

        clock_t start, end;
        double duration;

        for (int n = 65; n < 129; n++) {
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
        for (int n = 129; n < 257; n++) {
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
        int n = 512;
        for (int i = 0; i < 3; i++) {
            printf("Computing for: %d.\n", n);
            double** A = allocate_matrix(n, 1);

            start = clock();
            double** I = identity(n);
            lu_inv(A, I, n);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "LU,%d,%f\n", n, duration);

            start = clock();
            strassen_inv(A, n, naive_mult);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "SN,%d,%f\n", n, duration);

            start = clock();
            strassen_inv(A, n, strassen_mult);
            end = clock();
            duration = ((double)(end - start)) / CLOCKS_PER_SEC;

            fprintf(fp, "SS,%d,%f\n", n, duration);

            printf("Done.\n");
            n = n * 2;
        }
    }

    return 0;
}
