#ifndef STRASSEN_MULTIPLICATION_H_
#define STRASSEN_MULTIPLICATION_H_

void strassen_mult(double** A, double** B, double** C, int n);
double** pad_upper(double** A, int n);

#endif // STRASSEN_MULTIPLICATION_H_
