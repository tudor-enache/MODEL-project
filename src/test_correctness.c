#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/lu_decomposition.h"
#include "../include/lu_inversion.h"
#include "../include/naive_multiplication.h"
#include "../include/strassen_inversion.h"
#include "../include/strassen_multiplication.h"

int main() {
    // check Strassen Multiplication for NP2 matrices
    // check padding too
    // maybe already run timings and plot
    double** A = pad_upper(allocate_matrix(3, 1), 3);
    double** B = pad_upper(allocate_matrix(3, 1), 3);
    double** result = allocate_matrix(4, 0);
    print_matrix(A, 4);
    printf("\n");
    print_matrix(B, 4);
    printf("\n");

    naive_mult(A, B, result, 4);
    print_matrix(result, 4);
    printf("\n");

    strassen_mult(A, B, result, 4);
    print_matrix(result, 4);
    printf("\n");

    // time both types of multiplication
    // int n = 1024;
    // double** A = allocate_matrix(n, 1);
    // double** B = allocate_matrix(n, 1);
    // double** result_naive = allocate_matrix(n, 0);
    // double** result_strassen = allocate_matrix(n, 0);

    // clock_t start = clock();
    // naive_mult(A, B, result_naive, n);
    // clock_t end = clock();
    // double time_taken_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Naive Matrix Multiplication took %f seconds\n", time_taken_naive);

    // start = clock();
    // strassen_mult(A, B, result_strassen, n);
    // end = clock();
    // double time_taken_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Strassen's Matrix Multiplication took %f seconds\n", time_taken_strassen);

    // free_matrix(A, n);
    // free_matrix(B, n);
    // free_matrix(result_naive, n);
    // free_matrix(result_strassen, n);

    return 0;
}
