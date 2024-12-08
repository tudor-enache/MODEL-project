#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int next_power_of_two(int n);

double** allocate_matrix(int rows, int cols);

void free_matrix(double** matrix, int rows);

void print_matrix(double** matrix, int rows, int cols);

void brute_force(double** A, double** B, double** C, int n, int m, int p);

void add(double** A, double** B, double** result, int size);

void subtract(double** A, double** B, double** result, int size);

void strassen(double** A, double** B, double** C, int n);

#endif
