#ifndef stack_h
#define stack_h

struct List
{
    int value;
    struct List* next;
    int number;
};


    struct List* push(struct List* stack, int i);
    int getCount(struct List* stack);
    int isEmpty(struct List* stack);
    struct List* Delete(struct List* stack); //Interface BUG! This function is not needed for user of stack
    int pop(struct List** stack);
    struct List* DeleteAll(struct List* stack);

#endif
