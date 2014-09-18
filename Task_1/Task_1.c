#include <stdio.h>
#include <math.h>
int main()
{
    int a = 0, b = 0, c = 0;
    printf ("Input a, b, c with space and without points or commas\n");
    scanf ("%d %d %d", &a, &b, &c);
    Square (a, b, c);
    return 0;
}
int Square (int a, int  b, int c) 
{
    int d = 0, x1 = 0, x2 = 0;
    if (a == 0)
    {
        if (b ==0)
        {
             if (c == 0)
             printf("Solution is any number");
             else
             printf ("No solution");
        }
        else
        {
             x1 =((-1)*c)/b;
             printf ("%d", x1);
        }
    }
    else
    {
        d = pow (b, 2) - 4*a*c;
        if (d > 0)
        {
            x1 = ((-1)*b - sqrt(d))/(2*a);
            x2 = ((-1)*b + sqrt(d))/(2*a);
            printf ("%d, %d", x1, x2);
        }
        else
            if (d == 0)
            {
                x1 = ((-1)*b)/(2*a);
                printf ("%d", x1);
            }
            else
            printf ("No solution");
    }
system("PAUSE");	
return 0;
}
