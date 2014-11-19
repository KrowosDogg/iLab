#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "func.h"
#include "stackBridge.h"

int testStackWork()
{
    stackBridge A;
    stackBridge_init(&A);
    for(int i = 0; i < 10; i++)
    {
        printf("pushing: %d\n", i);
        stackBridge_push(&A, i);
    }
    while(!stackBridge_is_empty(&A))
        printf("popped: %d\n", stackBridge_pop(&A));

    stackBridge_delete(&A);
    return 0;
}

void printHelp()
{
    printf("Usage:\n  opn.exe 32 5 +\nResult will be printed on the screen.\n"
           "Operations: +, -, *, / -- only binary ones.\n");
}

char ** parceLexems(char *line, int *lexems_number)
{
    const int max_lexems_number = 10000;
    char **lexems = (char **)calloc(sizeof(char*), max_lexems_number);
    lexems[0] = strtok(line, " ");
    *lexems_number = 1;
    int i;
    for(i = 1; ;i++)
    {
        lexems[i] = strtok(NULL, " ");
        if (lexems[i] == NULL)
            break;
        (*lexems_number)++;
    }
    return lexems;
}
void printlexems(char**lexems,int lexems_number)
{
    int i;
    for (i=0; i < lexems_number; i++)
        printf ("%s\n", lexems [i]);
}
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        printHelp();
        printf("calculated: %d\n", PostfixCalc(argc - 1, argv + 1));
    }

    char **lexems;
    int lexems_number;
    char line[10000] = "";
    char c = 0;
    while ((c = getchar()) > 0)
    {
        line[strlen(line)] = c;
    }
    lexems = parceLexems(line, &lexems_number);
    printf ("lexems number: %d\n", lexems_number);
    printlexems(lexems, lexems_number);
    printf("calculated: %d\n", PostfixCalc(lexems_number, lexems));
    return 0;
}
