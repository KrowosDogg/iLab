#include "stackBridge.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void stackBridge_push (stackBridge *S, int value)
{
    S->listBegin = push(S->listBegin, value);
}

int stackBridge_pop (stackBridge *S)
{
    if (stackBridge_is_empty(S))
        return -1; //BUG. Need to throw exception here.
    int value = stackBridge_top(S);

    struct List *temp = S->listBegin;
    S->listBegin = S->listBegin->next;
    free(temp);

    return value;
}

int stackBridge_top(const stackBridge *S)
{
    return S->listBegin->value;
}

int stackBridge_is_empty (const stackBridge *S)
{
        return (S->listBegin->number == 0);
}

int stackBridge_is_full (const stackBridge *S)
{
    return 0; //—читаем, что никогда не переполн€етс€
}

void stackBridge_init (stackBridge *S)
{
    if (S == NULL)
    {
        printf("Wrong stack usage! NULL stack given!\n");
        exit(1);
    }
    S->listBegin = (struct List* )calloc(sizeof(struct List), 1);
    S->listBegin->next = NULL;
    S->listBegin->number = 0;
}

void stackBridge_delete (stackBridge *S)
{
    DeleteAll(S->listBegin);
    S->listBegin = NULL;
}
