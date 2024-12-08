#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "naive_matrix_multiply.h" 
#include "strassen.h"

int main() {
    int n = 1024; // Matrix size (adjust this for performance testing)
    double** A = allocate_matrix(n, n);
    double** B = allocate_matrix(n, n);
    double** result_naive = allocate_matrix(n, n);
    double** result_strassen = allocate_matrix(n, n);

 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }


    clock_t start = clock();
    naive_matrix_multiply(A, B, result_naive, n, n, n);
    clock_t end = clock();
    double time_taken_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Naive Matrix Multiplication took %f seconds\n", time_taken_naive);

    start = clock();
    strassen(A, B, result_strassen, n);
    end = clock();
    double time_taken_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Strassen's Matrix Multiplication took %f seconds\n", time_taken_strassen);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result_naive, n);
    free_matrix(result_strassen, n);

    return 0;
}
