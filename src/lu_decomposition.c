// TABASSUM BIBI SAARAH KHODADIN
// HOCINE LOUBAR
// TUDOR ENACHE

#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/lu_decomposition.h"

int lu_decomp(double** U, double** L, int n) {
    for (int i = 0; i < n; i++) {
        // find row with non-zero first entry
        int j = i;
        while (j < n && U[j][i] == 0) {
            j += 1;
        }
        if (j == n) {
            return 1;
        }

        // else found row with non-zero first entry, so swap with ith row
        double t;
        for (int k = i; k < n; k++) {
            t = U[i][k];
            U[i][k] = U[j][k];
            U[j][k] = t;
        }

        // now reduce rows; at the same time record changes in L
        for (j = i + 1; j < n; j++) {
            double r = U[j][i] / U[i][i];
            for (int k = i; k < n; k++) {
                U[j][k] -=  U[i][k] * r;
            }
            L[j][i] = r;
        }
    }
    return 0;
}