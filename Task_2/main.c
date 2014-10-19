#include "stack.h"
#include "stack.c"

int main()
{
    myStack my;
    myStack_init(&my);

    int testing_stack_size = 10000;

    for(int i = 0; i < testing_stack_size; i++)
    {
        myStack_push(&my, i);
    }
    for(int i = testing_stack_size - 1; i >= 0; i--)
    {
        if (myStack_is_empty(&my))
        {
            printf("Stack is empty... Can't continue algorithm.\n");
            return -1;
        }
        int returned_value = myStack_pop(&my);
        if (returned_value != i)
        {
            printf ("Your stack doesn't work! Returned = %d, awaited = %d\n", returned_value, i);
            return 1;
        }
    }

    myStack_delete(&my);
    if (!myStack_is_empty(&my))
    {
        printf ("Your stack doesn't work! Not empty after delete!\n");
        return 2;
    }
    printf ("Congratulations! Your stack works!\n");

    return 0;
}
