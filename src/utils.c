#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"

// Function to calculate the next power of two
int next_power_of_two(int n) {
    if (n <= 1) return 1; 
    int power = 1;
    while (power < n) power *= 2;
    return power;
}

// Allocate matrix
// Initialize to 0 at the same time
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