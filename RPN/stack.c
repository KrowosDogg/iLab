#include <stdlib.h>

#include "stack.h"

struct List* push(struct List* stack, int i)
{
   struct List* temp = stack;
   stack = (struct List*)calloc(1, sizeof(struct List));
   stack->value = i;
   stack->next = temp;
   stack->number = temp->number + 1; //BUG! What if temp is NULL???
   return stack;
}

int getCount(struct List* stack)
{
    int a = 0;
    while (!isEmpty(stack))
    {
        a++;
        stack = stack->next;
    }
    return a;
}

int isEmpty(struct List* stack)
{
    if (stack == NULL)
        return 1;
    else
        return 0;
}

struct List* Delete(struct List* stack)
{
    struct List* temp = stack;
    stack = stack->next;
    free(temp);
    return stack;
}

int pop(struct List** stack)
{
    int a;
    struct List* temp = *stack;
    a = temp->value;
    *stack = temp->next;
    free(temp);
    return a;
}

struct List* DeleteAll(struct List* stack)
{
    while(!isEmpty(stack))
    {
        struct List* temp = stack;
        stack = stack->next;
        free(temp);
    }
    return stack;
}
