#ifndef _STACK_BRIDGE_H_
#define _STACK_BRIDGE_H_

struct stackBridge_t
{
    struct List *listBegin;
};

typedef struct stackBridge_t stackBridge;

void stackBridge_push (stackBridge *S, int value);
int stackBridge_pop (stackBridge *S);
int stackBridge_top(const stackBridge *S);

int stackBridge_is_empty (const stackBridge *S);
int stackBridge_is_full (const stackBridge *S);

void stackBridge_init (stackBridge *S);
void stackBridge_delete (stackBridge *S);

#endif
