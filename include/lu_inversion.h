#ifndef LU_INVERSION_H_
#define LU_INVERSION_H_

void solve_upper_triangular(double** U, double* x, double* y, int n);
void solve_lower_triangular(double** L, double* y, double* b, int n);
double** lu_inv(double** U, double** L, int n);

#endif // LU_INVERSION_H_
