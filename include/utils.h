#ifndef UTILS_H
#define UTILS_H

int next_power_of_two(int n);
double** allocate_matrix(int rows, int cols);
void free_matrix(double** matrix, int rows);
void print_matrix(double** matrix, int rows, int cols);
void add(double** A, double** B, double** result, int size);
void subtract(double** A, double** B, double** result, int size);

#endif // UTILS_H