// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>

#include "../include/naive_multiplication.h"

// assume matrices are square of same dimension
void naive_mult(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}