const int NO_ROOTS = -1, INFINITE_ROOTS = 1, ONE_ROOTS = 2, TWO_ROOTS = 3;
int in (double *a, double *b, double *c)
{
    printf ("Input a, b, c without space or commas\n");
    while (scanf("%lg %lg %lg", a, b, c) <= 2)
    {
    do getchar();
        while (getchar()!='\n');
    printf("Incorrect input. Re-enter a, b, c\n");
    }
}

int out (double a, double b, double c, double *x1, double *x2)
{
   if (square (a, b, c, x1, x2) == INFINITE_ROOTS )
        printf("Solution is any number\n");
    else if (square (a, b, c, x1, x2) ==  NO_ROOTS)
        printf ("No solution\n");
        else if (square (a, b, c, x1, x2) == ONE_ROOTS)
        printf ("%lg\n", *x1);
            else if (square (a, b, c, x1, x2) == TWO_ROOTS)
            printf ("%lg, %lg\n", *x1, *x2);
            return 0;
}

int square (double a, double b, double c, double *x1, double *x2)
{    
    double d = 0;
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            return INFINITE_ROOTS;
            else 
            return NO_ROOTS;
        }                
        else  
            *x1 =((-1)*c)/b;
            return ONE_ROOTS;
    }
    else
    {
        d = pow (b, 2) - 4*a*c;
        if (d > 0)
        {
        *x1 = ((-1)*b - sqrt(d))/(2*a);
        *x2 = ((-1)*b + sqrt(d))/(2*a);
        return TWO_ROOTS;
        }
        else if (d == 0)
        {
            *x1 = -b / 2*a;
            return ONE_ROOTS;
        }
            else
            return NO_ROOTS;
    }
}
