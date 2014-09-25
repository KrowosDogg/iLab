#include <stdio.h>
#include <math.h>
#include "solve.h"
int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    in (&a, &b, &c);
    square (a, b, c, &x1, &x2);
    out (a, b, c, &x1, &x2);
    system ("PAUSE");
    return 0;
}
