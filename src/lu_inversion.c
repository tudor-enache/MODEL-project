// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/lu_inversion.h"

// inversion using the LU decomposition is done by solving n linear systems
// one for each column of the inverse
// need 3 functions:
// 1. solve upper triangular systems
// 2. solve lower triangular systems
// 3. inverse which puts everything together

void solve_upper_triangular(double** U, double* x, double* b, int n) {
    for (int i = n-1; i >= 0; i--) {
        x[i] = b[i];
    }
    for (int i = n-1; i >= 0; i--) {
        x[i] /= U[i][i];
        for (int j = i-1; j >= 0; j--) {
            x[j] -= x[i] * U[j][i];
        }
    }
}

void solve_lower_triangular(double** L, double* x, double* b, int n) {
    for (int i = 0; i < n; i++) {
        x[i] = b[i];
    }
    for (int i = 0; i < n; i++) {
        x[i] /= L[i][i];
        for (int j = i+1; j < n; j++) {
            x[j] -= x[i] * L[j][i];
        }
    }
}

// we work by resetting arrays
// this should give good performance
double** lu_inv(double** U, double** L, int n) {
    double** A_inv = allocate_matrix(n, 0);
    double* x = (double*)calloc(n, sizeof(double));
    double* y = (double*)calloc(n, sizeof(double));
    double* b = (double*)calloc(n, sizeof(double));

    // build unit column 1 in b
    b[0] = 1;

    solve_lower_triangular(L, y, b, n);
    solve_upper_triangular(U, x, y, n);

    // set first column of the inverse to x
    for (int i = 0; i < n; i++) {
        A_inv[i][0] = x[i];
    }

    for (int i = 1; i < n; i++) {
        // build unit column; reset x and y
        b[i - 1] = 0;
        b[i] = 1;
        for (int j = 0; j < n; j++) {
            x[j] = 0;
            y[j] = 0;
        }

        solve_lower_triangular(L, y, b, n);
        solve_upper_triangular(U, x, y, n);

        for (int j = 0; j < n; j++) {
            A_inv[j][i] = x[j];
        }
    }

    free(x);
    free(y);
    free(b);

    return A_inv;
}