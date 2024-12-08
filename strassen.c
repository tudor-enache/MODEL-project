#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the next power of two
int next_power_of_two(int n) {
    if (n <= 1) return 1; 
    int power = 1;
    while (power < n) power *= 2;
    return power;
}

// Allocate matrix
double** allocate_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)calloc(cols, sizeof(double));
    }
    return matrix;
}

// Free matrix
void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Print matrix
void print_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%0.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Brute force multiplication
void brute_force(double** A, double** B, double** C, int n, int m, int p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Add matrices
void add(double** A, double** B, double** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Subtract matrices
void subtract(double** A, double** B, double** result, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's algorithm
void strassen(double** A, double** B, double** C, int n) {
    if (n <= 2) {
        brute_force(A, B, C, n, n, n);
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
    strassen(temp1, temp2, p1, new_size);

    subtract(g, e, temp1, new_size);
    strassen(d, temp1, p2, new_size);

    add(a, b, temp1, new_size);
    strassen(temp1, h, p3, new_size);

    subtract(b, d, temp1, new_size);
    add(g, h, temp2, new_size);
    strassen(temp1, temp2, p4, new_size);

    subtract(f, h, temp1, new_size);
    strassen(a, temp1, p5, new_size);

    add(c, d, temp1, new_size);
    strassen(temp1, e, p6, new_size);

    subtract(a, c, temp1, new_size);
    add(e, f, temp2, new_size);
    strassen(temp1, temp2, p7, new_size);

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

