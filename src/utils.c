// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

// calculate closest power of 2, above a given number n
int next_power_of_two(int n) {
    if (n <= 1) {
        return 1;
    }

    int power = 1;
    while (power < n) {
        power *= 2;
    }

    return power;
}

// populate keeps track of whether we should randomly initialize the values in the matrix
// this is because we do allocations for "temporary" matrices, i.e. that only store the result of some other computation
// so there is no need to initialize the values in these
double** allocate_matrix(int n, int populate) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(n, sizeof(double));
        if (populate) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 2 * ((double)rand() / RAND_MAX) - 1;
            }
        }
    }
    return matrix;
}

void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(double** A, double** B, double** result, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void initialize_random_generator() {
    srand(time(NULL));
}