#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

/**
 * struct Stack - A simple stack structure.
 * @stack: An array to store stack elements.
 * @top: The index of the top element in the stack.
 */
typedef struct Stack
{
	int stack[STACK_SIZE];
	int top;
} Stack;

void push(int value);
void pall(void);

#endif /* MONTY_H */
