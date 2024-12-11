#include <stdio.h>
#include <stdlib.h>

#include "../include/strassen_multiplication.h"
#include "../include/utils.h"
#include "../include/naive_multiplication.h"

// Strassen's algorithm
void strassen_mult(double** A, double** B, double** C, int n) {
    // change to larger number
    if (n <= 2) {
        naive_mult(A, B, C, n, n, n);
        return;
    }

    int new_size = n / 2;
    double** a = allocate_matrix(new_size, new_size);
    double** b = allocate_matrix(new_size, new_size);
    double** c = allocate_matrix(new_size, new_size);
    double** d = allocate_matrix(new_size, new_size);
    double** e = allocate_matrix(new_size, new_size);
    double** f = allocate_matrix(new_size, new_size);
    double** g = allocate_matrix(new_size, new_size);
    double** h = allocate_matrix(new_size, new_size);

    // Split matrices
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + new_size];
            c[i][j] = A[i + new_size][j];
            d[i][j] = A[i + new_size][j + new_size];
            e[i][j] = B[i][j];
            f[i][j] = B[i][j + new_size];
            g[i][j] = B[i + new_size][j];
            h[i][j] = B[i + new_size][j + new_size];
        }
    }

    // Allocate temporary matrices
    double** p1 = allocate_matrix(new_size, new_size);
    double** p2 = allocate_matrix(new_size, new_size);
    double** p3 = allocate_matrix(new_size, new_size);
    double** p4 = allocate_matrix(new_size, new_size);
    double** p5 = allocate_matrix(new_size, new_size);
    double** p6 = allocate_matrix(new_size, new_size);
    double** p7 = allocate_matrix(new_size, new_size);

    double** temp1 = allocate_matrix(new_size, new_size);
    double** temp2 = allocate_matrix(new_size, new_size);

    add(a, d, temp1, new_size);
    add(e, h, temp2, new_size);
    strassen_mult(temp1, temp2, p1, new_size);

    subtract(g, e, temp1, new_size);
    strassen_mult(d, temp1, p2, new_size);

    add(a, b, temp1, new_size);
    strassen_mult(temp1, h, p3, new_size);

    subtract(b, d, temp1, new_size);
    add(g, h, temp2, new_size);
    strassen_mult(temp1, temp2, p4, new_size);

    subtract(f, h, temp1, new_size);
    strassen_mult(a, temp1, p5, new_size);

    add(c, d, temp1, new_size);
    strassen_mult(temp1, e, p6, new_size);

    subtract(a, c, temp1, new_size);
    add(e, f, temp2, new_size);
    strassen_mult(temp1, temp2, p7, new_size);

    // Combine results into C
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            C[i][j] = p1[i][j] + p2[i][j] - p3[i][j] + p4[i][j];
            C[i][j + new_size] = p5[i][j] + p3[i][j];
            C[i + new_size][j] = p6[i][j] + p2[i][j];
            C[i + new_size][j + new_size] = p5[i][j] + p1[i][j] - p6[i][j] - p7[i][j];
        }
    }

    // Free memory
    free_matrix(a, new_size);
    free_matrix(b, new_size);
    free_matrix(c, new_size);
    free_matrix(d, new_size);
    free_matrix(e, new_size);
    free_matrix(f, new_size);
    free_matrix(g, new_size);
    free_matrix(h, new_size);

    free_matrix(p1, new_size);
    free_matrix(p2, new_size);
    free_matrix(p3, new_size);
    free_matrix(p4, new_size);
    free_matrix(p5, new_size);
    free_matrix(p6, new_size);
    free_matrix(p7, new_size);

    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);
}