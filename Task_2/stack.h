#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

struct myStack_t
{
    int *A;
    int allocated_size; //max number of ints before the next allocation
    int number;
};

typedef struct myStack_t myStack;

void myStack_push (myStack *S, int value);
int myStack_pop (myStack *S);
int myStack_top(const myStack *S);

int myStack_is_empty (const myStack *S);
int myStack_is_full (const myStack *S);

void myStack_init (myStack *S);
void myStack_delete (myStack *S);

#endif
