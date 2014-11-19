#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <math.h>

enum ROOTS
{
    INFINITE_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS,
    NO_ROOTS,
};

void in (double *a, double *b, double *c);
void out (double x1, double x2, int root);
void square (double a, double b, double c, double *x1, double *x2, int *root);

#endif
