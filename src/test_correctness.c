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
    // test correctness of multiplication functions
    // int m = 2;
    // double** C = allocate_matrix(m, 0);
    // double** D = allocate_matrix(m, 0);
    // double** result_1 = allocate_matrix(m, 0);

    // C[0][0] = 1; C[0][1] = 0;
    // C[1][0] = 0; C[1][1] = 1;

    // D[0][0] = 1; D[0][1] = 2;
    // D[1][0] = 3; D[1][1] = 4;

    // naive_mult(C, D, result_1, m);
    // print_matrix(result_1, m);
    // printf("\n");

    // strassen_mult(C, D, result_1, m);
    // print_matrix(result_1, m);
    // printf("\n");

    // double E_def[4][4] = {
    //     {1, 0, 0, 0},
    //     {0, 1, 0, 0},
    //     {0, 0, 1, 0},
    //     {0, 0, 0, 1}
    // };
    // double** E = allocate_matrix(4, 0);
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         E[i][j] = E_def[i][j];
    //     }
    // }

    // double F_def[4][4] = {
    //     {1, 2, 3, 4},
    //     {2, 3, 4, 5},
    //     {3, 4, 5, 6},
    //     {4, 5, 6, 7}
    // };
    // double** F = allocate_matrix(4, 0);
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         F[i][j] = F_def[i][j];
    //     }
    // }

    // double** result_2 = allocate_matrix(4, 0);

    // naive_mult(E, F, result_2, 4);
    // print_matrix(result_2, 4);
    // printf("\n");

    // strassen_mult(E, F, result_2, 4);
    // print_matrix(result_2, 4);    
    // printf("\n");

    // time both types of multiplication
    int n = 1024;
    double** A = allocate_matrix(n, 1);
    double** B = allocate_matrix(n, 1);
    double** result_naive = allocate_matrix(n, 0);
    double** result_strassen = allocate_matrix(n, 0);

    clock_t start = clock();
    naive_mult(A, B, result_naive, n);
    clock_t end = clock();
    double time_taken_naive = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Naive Matrix Multiplication took %f seconds\n", time_taken_naive);

    start = clock();
    strassen_mult(A, B, result_strassen, n);
    end = clock();
    double time_taken_strassen = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Strassen's Matrix Multiplication took %f seconds\n", time_taken_strassen);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result_naive, n);
    free_matrix(result_strassen, n);

    // check creation of random matrices for a few different sizes
    // initialize_random_generator();

    // int sizes[5] = {1, 2, 4, 8, 16};
    // for (int i = 0; i < 5; i++) {
    //     double** A = allocate_matrix(sizes[i], 1);
    //     print_matrix(A, sizes[i]);
    //     printf("\n");
    // }

    return 0;
}
