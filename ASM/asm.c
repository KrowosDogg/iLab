#include <stdio.h>
#include <stdlib.h>

#include "libarch.h"

char help_string[] = "asm.exe <source file name> <destination binary file name>\n";

void assembleFile(FILE *f_source, FILE *f_destination);

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf(help_string);
        exit(0);
    }
    FILE *f_source;
    FILE *f_destination;
    f_source = fopen(argv[1], "r");
    f_destination = fopen(argv[2], "w");
    assembleFile(f_source, f_destination);

    return 0;
}

void assembleFile(FILE *f_source, FILE *f_destination)
{
    while (!feof(f_source))
    {
        tCommandWithOperands command = readCommandFromFile(f_source);
        tCode code = makeCodeFromCommandWithOperands(command);
        writeCodeToBinaryFile(f_destination, code);
        free(code.words);
    }
    printf("Successfully assembled file.\n");
}
