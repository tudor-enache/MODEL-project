// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/strassen_inversion.h"

// assume matrices are square of same dimension, a power of 2
// further assume all submatrices a and Z are invertible
// (for analysis) if they are not, we simply retry
double** strassen_inv(double** A, int n, void (*mult)(double**, double**, double**, int)) {
    if (n == 1) {
        double** A_inv = allocate_matrix(n, 0);
        A_inv[0][0] = 1 / A[0][0];
        return A_inv;
    }

    int new_size = n / 2;
    double** a = allocate_matrix(new_size, 0);
    double** b = allocate_matrix(new_size, 0);
    double** c = allocate_matrix(new_size, 0);
    double** d = allocate_matrix(new_size, 0);
    double** e = allocate_matrix(new_size, 0);

    double** Z = allocate_matrix(new_size, 0);

    double** x = allocate_matrix(new_size, 0);
    double** y = allocate_matrix(new_size, 0);
    double** z = allocate_matrix(new_size, 0);
    double** t = allocate_matrix(new_size, 0);

    double** temp1 = allocate_matrix(new_size, 0);
    double** temp2 = allocate_matrix(new_size, 0);
    double** temp3 = allocate_matrix(new_size, 0);

    // split matrix
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            a[i][j] = A[i][j];
            b[i][j] = A[i][j + new_size];
            c[i][j] = A[i + new_size][j];
            d[i][j] = A[i + new_size][j + new_size];
        }
    }

    e = strassen_inv(a, new_size, mult);
    
    // calculate Z
    mult(c, e, temp1, new_size);
    mult(temp1, b, Z, new_size);
    subtract(d, Z, Z, new_size);

    t = strassen_inv(Z, new_size, mult);

    // calculate eb and ce
    mult(e, b, temp1, new_size);
    mult(c, e, temp2, new_size);

    mult(temp1, t, temp3, new_size);
    subtract(y, temp3, y, new_size);

    mult(t, temp2, temp3, new_size);
    subtract(z, temp3, z, new_size);

    mult(temp1, t, temp3, new_size);
    mult(temp3, temp2, x, new_size);
    add(x, e, x, new_size);

    // allocate space for the inverse and write the result into it
    double** A_inv = allocate_matrix(n, 0);
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            A_inv[i][j] = x[i][j];
            A_inv[i][j + new_size] = y[i][j];
            A_inv[i + new_size][j] = z[i][j];
            A_inv[i + new_size][j + new_size] = t[i][j];
        }
    }

    free_matrix(a, new_size);
    free_matrix(b, new_size);
    free_matrix(c, new_size);
    free_matrix(d, new_size);
    free_matrix(e, new_size);
    free_matrix(Z, new_size);
    free_matrix(x, new_size);
    free_matrix(y, new_size);
    free_matrix(z, new_size);
    free_matrix(t, new_size);
    free_matrix(temp1, new_size);
    free_matrix(temp2, new_size);
    free_matrix(temp3, new_size);
    
    return A_inv;
}