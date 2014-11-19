#include "func.h"

#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

#include "stackBridge.h"

int IsNumber (char *lexem)
{
    //FIXME in future -- correctness of number is not checked absolutely
    return lexem[0] <= '9' && lexem[0] >= '0';
}

int PostfixCalc (int N, char **lexems)
{
    stackBridge stack;
    stackBridge_init(&stack);

    if (stackBridge_is_empty(&stack))
        printf("Stack is empty now.\n");
    else
        printf("Stack includes something.\n");

    int c;
    for(c = 0; c < N; c++)
    {
        printf("lexem is %s\n", lexems[c]);
        if (IsNumber(lexems[c]))
        {
            tData number = atoi(lexems[c]);
            printf("number is %d\n", number);
            stackBridge_push(&stack, number);
        }
        else
        {
            printf("operation is %s\n", lexems[c]);
            tData result;
            tData b = stackBridge_pop(&stack);
            tData a = stackBridge_pop(&stack);
            switch (lexems[c][0])
            {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            };
            stackBridge_push(&stack, result);
        }
    }
    tData result = stackBridge_pop(&stack);
    if (!stackBridge_is_empty(&stack))
    {
        result = -1;
    }
    stackBridge_delete(&stack);
    return result;
}

