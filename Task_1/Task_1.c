#include <stdio.h>
#include <math.h>
int main()
{
    int a = 0, b = 0, c = 0, d = 0, x1 = 0, x2 = 0;
    printf ("Input a, b, c with space and without points or commas\n");
    scanf ("%d %d %d", &a, &b, &c);
    switch (a)
    {
           case 0: switch (b)
           {
                case 0: switch (c)
                {
                     case 0: printf("Solution is any number"); break;
                     default: printf ("No solution"); break;
                }
                break;
                default:  x1 =((-1)*c)/b;
                printf ("%d", x1); break;
           }
           break;
           default: d = pow (b, 2) - 4*a*c;
                    if (d >= 0)
                    {
                       x1 = ((-1)*b - sqrt(d))/(2*a);
                       x2 = ((-1)*b + sqrt(d))/(2*a);
                       printf ("%d, %d", x1, x2);
                    }
                    else 
                         printf ("No solution");
    }
system("PAUSE");	
return 0;
}
