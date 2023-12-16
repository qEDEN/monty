#include "monty.h"

Stack stack;

/**
 * push - Pushes an element onto the stack.
 * @value: The value to be pushed onto the stack.
 */
void push(int value)
{
	if (stack.top < STACK_SIZE)
	{
		stack.stack[stack.top++] = value;
	}
	else
	{
		fprintf(stderr, "Error: Stack overflow\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * pall - Prints all the values on the stack.
 */
void pall(void)
{
	int i;

	for (i = stack.top - 1; i >= 0; i--)
	{
		printf("%d\n", stack.stack[i]);
	}
}
