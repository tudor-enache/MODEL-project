#ifndef STRASSEN_INVERSION_H_
#define STRASSEN_INVERSION_H_

double** strassen_inv(double** A, int n, void (*mult)(double**, double**, double**, int));

#endif // STRASSEN_INVERSION_H_