#include <stdio.h>
#include <stdlib.h>

#include "../include/strassen_multiplication.h"
#include "../include/utils.h"
#include "../include/naive_multiplication.h"

// assume matrices are square of same dimension, a power of 2
// this means when testing our implementation, we pre-pad incompatible matrices
// anyways, let's keep the code this way for the moment, process and time in test, and then maybe change
void strassen_mult(double** A, double** B, double** C, int n) {
    // can test different numbers from which to switch to naive
    if (n <= 128) {
        naive_mult(A, B, C, n);
        return;
    }

    int new_size = n / 2;
    double** a = allocate_matrix(new_size, 0);
    double** b = allocate_matrix(new_size, 0);
    double** c = allocate_matrix(new_size, 0);
    double** d = allocate_matrix(new_size, 0);
    double** x = allocate_matrix(new_size, 0);
    double** y = allocate_matrix(new_size, 0);
    double** z = allocate_matrix(new_size, 0);
    double** t = allocate_matrix(new_size, 0);

    // split matrices
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + new_size];
            c[i][j] = A[i + new_size][j];
            d[i][j] = A[i + new_size][j + new_size];
            x[i][j] = B[i][j];
            y[i][j] = B[i][j + new_size];
            z[i][j] = B[i + new_size][j];
            t[i][j] = B[i + new_size][j + new_size];
        }
    }

    // allocate temporary matrices
    double** q1 = allocate_matrix(new_size, 0);
    double** q2 = allocate_matrix(new_size, 0);
    double** q3 = allocate_matrix(new_size, 0);
    double** q4 = allocate_matrix(new_size, 0);
    double** q5 = allocate_matrix(new_size, 0);
    double** q6 = allocate_matrix(new_size, 0);
    double** q7 = allocate_matrix(new_size, 0);

    double** temp1 = allocate_matrix(new_size, 0);
    double** temp2 = allocate_matrix(new_size, 0);
    
    add(x, z, temp1, new_size);
    strassen_mult(a, temp1, q1, new_size);

    add(y, t, temp1, new_size);
    strassen_mult(d, temp1, q2, new_size);

    subtract(d, a, temp1, new_size);
    subtract(z, y, temp2, new_size);
    strassen_mult(temp1, temp2, q3, new_size);

    subtract(b, d, temp1, new_size);
    add(z, t, temp2, new_size);
    strassen_mult(temp1, temp2, q4, new_size);

    subtract(b, a, temp1, new_size);
    strassen_mult(temp1, z, q5, new_size);

    subtract(c, a, temp1, new_size);
    add(x, y, temp2, new_size);
    strassen_mult(temp1, temp2, q6, new_size);

    subtract(c, d, temp1, new_size);
    strassen_mult(temp1, y, q7, new_size);

    // combine results into C
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            C[i][j] = q1[i][j] + q5[i][j];
            C[i][j + new_size] = q2[i][j] + q3[i][j] + q4[i][j] - q5[i][j];
            C[i + new_size][j] = q1[i][j] + q3[i][j] + q6[i][j] - q7[i][j];
            C[i + new_size][j + new_size] = q2[i][j] + q7[i][j];
        }
    }

    // free memory
    free_matrix(a, new_size);
    free_matrix(b, new_size);
    free_matrix(c, new_size);
    free_matrix(d, new_size);
    free_matrix(x, new_size);
    free_matrix(y, new_size);
    free_matrix(z, new_size);
    free_matrix(t, new_size);

    free_matrix(q1, new_size);
    free_matrix(q2, new_size);
    free_matrix(q3, new_size);
    free_matrix(q4, new_size);
    free_matrix(q5, new_size);
    free_matrix(q6, new_size);
    free_matrix(q7, new_size);

    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);
}