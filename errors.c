#include "monty.h"

/**
 * monty_err - Prints appropriate error messages.
 * @error_code: The error codes are the following:
 * (1) => The user does not give any file or more than one file to the program.
 * (2) => The file provided is not a file that can be opened or read.
 * (3) => The file provided contains an invalid instruction.
 * (4) => When the program is unable to malloc more memory.
 * (5) => When the parameter passed to the instruction "push" is not an int.
 * (6) => When the stack it empty for pint.
 * (7) => When the stack it empty for pop.
 * (8) => When stack is too short for operation.
 */
void monty_err(int error_code, ...)
{
	va_list args;
	int line_num;
	char *op;

	va_start(args, error_code);

	switch (error_code)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
			break;
		case 3:
			line_num = va_arg(args, int);
			op = va_arg(args, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", line_num, op);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
			break;
		default:
			break;
	}

	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * monty_more_err - Handles errors for pint, pop, stack-related errors.
 * @error_code: The error codes are the following:
 * (6) => When the stack it empty for pint.
 * (7) => When the stack it empty for pop.
 * (8) => When stack is too short for operation.
 * (9) => Division by zero.
 */
void monty_more_err(int error_code, ...)
{
	va_list args;
	int line_num;
	char *op;

	va_start(args, error_code);

	switch (error_code)
	{
		case 6:
			line_num = va_arg(args, int);
			fprintf(stderr, "L%d: can't pint, stack empty\n", line_num);
			break;
		case 7:
			line_num = va_arg(args, int);
			fprintf(stderr, "L%d: can't pop an empty stack\n", line_num);
			break;
		case 8:
			line_num = va_arg(args, unsigned int);
			op = va_arg(args, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", line_num, op);
			break;
		case 9:
			line_num = va_arg(args, unsigned int);
			fprintf(stderr, "L%d: division by zero\n", line_num);
			break;
		default:
			break;
	}

	free_nodes();
	exit(EXIT_FAILURE);
}

/**
 * monty_string_err - Handles errors for pchar and other string-related errors.
 * @error_code: The error codes are the following:
 * (10) => The number inside a node is outside ASCII bounds.
 * (11) => The stack is empty.
 */
void monty_string_err(int error_code, ...)
{
	va_list args;
	int line_num;

	va_start(args, error_code);
	line_num = va_arg(args, int);

	switch (error_code)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", line_num);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", line_num);
			break;
		default:
			break;
	}

	free_nodes();
	exit(EXIT_FAILURE);
}
