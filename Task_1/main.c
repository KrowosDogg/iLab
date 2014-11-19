#include "func.h"
#include "func.ñ"

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int root = TWO_ROOTS;
    in (&a, &b, &c);
    square (a, b, c, &x1, &x2, &root);
    out (x1, x2, root);
    system ("PAUSE");
    return 0;
}
