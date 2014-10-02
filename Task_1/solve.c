#ifndef func
#define func

enum ROOTS
{
    INFINITE_ROOTS,
    ONE_ROOTS,
    TWO_ROOTS,
    NO_ROOTS,
};

void in (double *a, double *b, double *c)
{
    printf ("Input a, b, c without space or commas\n");
    while (scanf("%lg %lg %lg", a, b, c) <= 2)
    {
    do getchar();
        while (getchar()!='\n');
    printf("Incorrect input. Re-enter a, b, c\n");
    }
}

void square (double a, double b, double c, double *x1, double *x2, int *root)
{
    double d = 0;
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            *root = INFINITE_ROOTS;
            else
            *root = NO_ROOTS;
        }
        else
            *x1 =((-1)*c)/b;
            *root = ONE_ROOTS;
    }
    else
    {
        d = pow (b, 2) - 4*a*c;
        if (d > 0)
        {
        *x1 = ((-1)*b - sqrt(d))/(2*a);
        *x2 = ((-1)*b + sqrt(d))/(2*a);
        *root = TWO_ROOTS;
        }
        else if (d == 0)
        {
            *x1 = -b / 2*a;
            *root = ONE_ROOTS;
        }
            else
            *root = NO_ROOTS;
    }
}

void out (double *x1, double *x2, int *root)
{
    switch(*root)
        {
            case INFINITE_ROOTS:
                printf("Solution is any number\n");
                break;
            case NO_ROOTS:
                printf("No solution\n");
                break;
            case ONE_ROOTS:
                printf ("%lg\n", *x1);
                break;
            case TWO_ROOTS:
                printf ("%lg, %lg\n", *x1, *x2);
                break;
        }
}
#endif
