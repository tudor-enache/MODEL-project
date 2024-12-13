#ifndef UTILS_H
#define UTILS_H

int next_power_of_two(int n);
double** allocate_matrix(int n, int populate);
void free_matrix(double** matrix, int n);
void print_matrix(double** matrix, int n);
void add(double** A, double** B, double** result, int n);
void subtract(double** A, double** B, double** result, int n);
void initialize_random_generator();
double** pad_upper(double** A, int n);

#endif // UTILS_H