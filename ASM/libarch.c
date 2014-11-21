#include "libarch.h"

#include <string.h>

//char* registers[REGISTERS_NUMBER] =
  //   {NULL, "IP", "SP", "FLAGS", "AX", "BX", "CX", "DX"};

//int operandsNumberForCommandType[COMMAND_TYPES_NUMBER] = {2, 2, 1, 1, 1};

extern int operandsNumberForCommandType[COMMAND_TYPES_NUMBER] = {2, 2, 1, 1, 1};

extern char* registers[REGISTERS_NUMBER] =
     {NULL, "IP", "SP", "FLAGS", "AX", "BX", "CX", "DX"};

extern char* command [COMMAND_TYPES_NUMBER][MAX_COMMANDS_NUMBER_IN_TYPE] =
    {{"mov", "add", "sub", "mul", "div", NULL},
	 {"xor", "and", "or", "not", NULL},
     {"jmp", "je", "jne", "jg", "jge", "jl", "jle", NULL},
     {"push", "pop", NULL},
     {"print", "input", NULL}};


tCommand parseCommand(char *cmd_name)
{
	tCommand cmd;
    for ( cmd.type = 0;
		  cmd.type < COMMAND_TYPES_NUMBER;
		  cmd.type++)
    {
        for (cmd.index = 0;
			 command [cmd.type][cmd.index] != NULL;
			 cmd.index++)
        {
            if (strcmp(command [cmd.type][cmd.index], cmd_name) == 0) //strings equal
            {
                return cmd;
            }
        }
    }
	printf("Compilation errror!\n");
	exit(-1);
}

char *commandName(tCommand cmd)
{
	return command[cmd.type][cmd.index];
}

tOperand parseOperand(char *op_name)
{
	tOperand op;
	if (op_name[0] >= '0' && op_name[0] <= '9')
	{
		op.type = NUMBER;
		op.value = atoi(op_name);
		return op;
	}
	for (op.type = 1; op.type < REGISTERS_NUMBER; op.type++)
		if (strcmp(registers[op.type], op_name) == 0)
		{
			return op;
		}
    op.type = -1;
    printf("Wrong register or number!\n");
    exit(-1);
    return op;
}

char buffer_for_number[10];
char * operandName(tOperand op)
{
	if (op.type == NUMBER)
	{
		snprintf(buffer_for_number, 10, "%d", op.value);
		return buffer_for_number;
	}
	return registers[op.type];
}

tWord makeCodeWordFromNumbers(int a, int b, int c, int d)
{
	tWord res;
	res = ((a&0xF) << 12) | ((b&0xF) << 8) | ((c&0xF) << 4) | (d&0xF);
	return res;
}

void makeNumbersFromCodeWord(tWord word, int *a, int *b,
							int *c, int *d)
{
	*a = (word >> 12)&0xF;
	*b = (word >> 8)&0xF;
	*c = (word >> 4)&0xF;
	*d = word&0xF;
}

//assembling of command with operands
tCode makeCodeFromCommandWithOperands(tCommandWithOperands cmd)
{
    tCode code;
	if (operandsNumberForCommandType[cmd.cmd.type] == 2
        && cmd.right.type == NUMBER && cmd.left.type == NUMBER)
    {
		printf("Wrong code found!\n");
		exit(-2);
	}

    code.size = 1;
	if ((operandsNumberForCommandType[cmd.cmd.type] == 1 && cmd.left.type == NUMBER) ||
        (operandsNumberForCommandType[cmd.cmd.type] == 2 && (cmd.left.type == NUMBER || cmd.right.type == NUMBER)))
    {
        code.size = 2;
    }
    code.words = (tWord *)malloc(sizeof(tWord)*code.size);
    if (code.words == NULL)
    {
        printf("Error: No memory!\n");
        exit(-3);
    }
	code.words[0] = makeCodeWordFromNumbers(cmd.cmd.type,
										cmd.cmd.index,
										cmd.left.type,
										cmd.right.type);
	if ((operandsNumberForCommandType[cmd.cmd.type] == 1 && cmd.left.type == NUMBER) ||
        (operandsNumberForCommandType[cmd.cmd.type] == 2 && cmd.left.type == NUMBER))
    {
        code.words[1] = cmd.left.value;
    }
    else if (operandsNumberForCommandType[cmd.cmd.type] == 2 && cmd.right.type == NUMBER)
    {
        code.words[1] = cmd.right.value;
    }
    return code;
}

//disassembling of command
tCommandWithOperands makeCommandWithOperands(tCode code)
{
    tCommand cmd;
    int left, right;
    int cmd_type;
	makeNumbersFromCodeWord(code.words[0], &cmd_type, &cmd.index, &left, &right);
	cmd.type = cmd_type;
	tCommandWithOperands cmdWithOperands;
	cmdWithOperands.cmd = cmd;
	//FIXME: maybe need to check code correctness (zeroes if no operands for the command type)
	cmdWithOperands.left.type = left;
	cmdWithOperands.right.type = right;
    if ((operandsNumberForCommandType[cmd.type] == 1 && left == NUMBER) ||
        (operandsNumberForCommandType[cmd.type] == 2 && left == NUMBER))
    {
        cmdWithOperands.left.value = code.words[1];
    }
    else if (operandsNumberForCommandType[cmd.type] == 2 && right == NUMBER)
    {
        cmdWithOperands.right.value = code.words[1];
    }
    return cmdWithOperands;
}

//returns command size in words depending on the first command word
int codeSize(tWord word)
{
    int cmd_type = (word >> 12) & 0xF;
    int left_type = (word >> 4) & 0xF;
    int right_type = word & 0xF;
    if (operandsNumberForCommandType[cmd_type] == 0)
        return 1;
    else if (operandsNumberForCommandType[cmd_type] == 1)
        if (left_type == NUMBER)
            return 2;
        else
            return 1;
    else if (operandsNumberForCommandType[cmd_type] == 2)
        if (left_type == NUMBER && right_type == NUMBER)
            return 3;
        else if (left_type == NUMBER || right_type == NUMBER)
            return 2;
        else
            return 1;
    else
        return -1; //should never happens
}

//reads code from the file depending on its size
tCode readCodeFromBinaryFile(FILE *f)
{
    tCode code;
    tWord word;
    fread(&word, sizeof(word), 1, f); //FIXME: may be reading errors
    code.size = codeSize(word);
    code.words = (tWord*) calloc(sizeof(tWord), code.size);
    code.words[0] = word;
    for (int i = 1; i < code.size; i++)
    {
        fread(&word, sizeof(word), 1, f); //FIXME: may be reading errors
        code.words[i] = word;
    }
    return code;
}
//writes code from the file depending on its size
void writeCodeToBinaryFile(FILE *f, tCode code)
{
    fwrite(code.words, sizeof(tWord), code.size, f); //FIXME: may be reading errors
}

tCommandWithOperands parseLine(tLine line)
{
    char cmd_name[MAX_COMMAND_LENGTH];
    sscanf(line.str, "%s", cmd_name);
    tCommand cmd = parseCommand(cmd_name);
    tCommandWithOperands command_with_operands = {cmd, {0, 0}, {0, 0}};
    int operands_number = operandsNumberForCommandType[cmd.type];
    if (operands_number == 0)
        return command_with_operands;
    else if (operands_number == 1)
    {
        char operand_name[10];
        sscanf(line.str, "%s %s", cmd_name, operand_name);
        tOperand op = parseOperand(operand_name);
        command_with_operands.left = op;
    }
    else if (operands_number == 2)
    {
        char operand1_name[10], operand2_name[10];
        sscanf(line.str, "%s %s, %s", cmd_name, operand1_name, operand2_name);
        tOperand op1 = parseOperand(operand1_name);
        command_with_operands.left = op1;
        tOperand op2 = parseOperand(operand2_name);
        command_with_operands.right = op2;
    }
    else //exception
    {
        printf("Wrong number of operands!!!\n");
        exit(-1);
    }
    return command_with_operands;
}

tLine makeLine(tCommandWithOperands command_with_operands)
{
    tLine line;
    int operands_number = operandsNumberForCommandType[command_with_operands.cmd.type];
    if (operands_number == 0)
    {
        snprintf(line.str, MAX_COMMAND_LINE_LENGTH-1, "%s",
                 commandName(command_with_operands.cmd));
    }
    else if (operands_number == 1)
    {
        snprintf(line.str, MAX_COMMAND_LINE_LENGTH-1, "%s %s",
                 commandName(command_with_operands.cmd),
                 operandName(command_with_operands.left));
    }
    else if (operands_number == 2)
    {
        snprintf(line.str, MAX_COMMAND_LINE_LENGTH-1, "%s %s, %s",
                 commandName(command_with_operands.cmd),
                 operandName(command_with_operands.left),
                 operandName(command_with_operands.right));
    }
    return line;
}

//reads command from the file depending on its size
tCommandWithOperands readCommandFromFile(FILE *f)
{
    tLine line;
    fgets(line.str, MAX_COMMAND_LINE_LENGTH-1, f);
    return parseLine(line);
}

//writes command from the file depending on its size
void writeCommandToFile(FILE *f, tCommandWithOperands command_with_operands)
{
    tLine line = makeLine(command_with_operands);
    fputs(line.str, f);
}
