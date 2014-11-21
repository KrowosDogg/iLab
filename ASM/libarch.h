#ifndef LIBARCH_H
#define LIBARCH_H

#include <stdlib.h>
#include <stdio.h>

#define COMMAND_TYPES_NUMBER 5
#define MAX_CODE_LENGTH 2
#define WORD_SIZE 2
#define MAX_COMMAND_LENGTH 5
#define MAX_COMMANDS_NUMBER_IN_TYPE 8
#define MAX_COMMAND_LINE_LENGTH 100
#define REGISTERS_NUMBER 8

//16-bit architecture!!!
typedef unsigned short int tWord;

enum eCommandType {ARITHMETICAL_OP, LOGICAL_OP, JUMP_OP, STACK_OP, IO_OP};

enum eRegister {NUMBER, IP, SP, FLAGS, AX, BX, CX, DX};

typedef struct {
    enum eCommandType type;
	int index;
} tCommand;

tCommand parseCommand(char *cmd_name);
char *commandName(tCommand cmd);

typedef struct {
	enum eRegister type;
	tWord value; //if type == NUMBER
} tOperand;

//find operand name in the list of operands name or finds its a number
tOperand parseOperand(char *op_name);
char * operandName(tOperand op);

typedef struct {
    tWord *words;
	size_t size;
} tCode;

typedef struct {
	tCommand cmd;
	tOperand left, right;
} tCommandWithOperands;

typedef struct {
	char str[MAX_COMMAND_LINE_LENGTH];
} tLine;

//assembling of command
tCode makeCodeFromCommandWithOperands(tCommandWithOperands cmd);
//disassembling of command
tCommandWithOperands makeCommandWithOperands(tCode code);

//returns command size in words depending on the first command word
int codeSize(tWord word);
//reads code from the file depending on its size
tCode readCodeFromBinaryFile(FILE *f);
//writes code from the file depending on its size
void writeCodeToBinaryFile(FILE *f, tCode code);

tCommandWithOperands parseLine(tLine);
tLine makeLine(tCommandWithOperands cmd);

//reads command from the file depending on its size
tCommandWithOperands readCommandFromFile(FILE *f);
//writes command from the file depending on its size
void writeCommandToFile(FILE *f, tCommandWithOperands);

#endif // LIBARCH_H
