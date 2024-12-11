#include <stdio.h>
#include <stdlib.h>

#include "../include/naive_multiplication.h"

// Naive multiplication algorithm
void naive_mult(double** A, double** B, double** C, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}