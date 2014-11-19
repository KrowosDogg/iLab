#ifndef func_h
#define func_h

typedef int tData;
typedef struct List* myStack;

int IsNumber (char *lexem);
int PostfixCalc (int N, char **lexems);

#endif
