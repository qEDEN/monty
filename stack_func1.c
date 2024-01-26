#include "monty.h"

/**
 * add_nd_to_stk - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @ln: Line number of the opcode (unused).
 */
void add_nd_to_stk(stack_t **new_node, __attribute__((unused)) unsigned int ln)
{
	stack_t *tmp;

	handle_error(new_node == NULL || *new_node == NULL,
			"Error: Failed to add node to stack\n");

	if (head == NULL)
	{
		head = *new_node;
		return;
	}

	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}

/**
 * print_stk_nodes - Prints all nodes in the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @ln: Line number of the opcode (unused).
 */
void print_stk_nodes(stack_t **stack, __attribute__((unused)) unsigned int ln)
{
	stack_t *tmp;

	handle_error(stack == NULL, "Error: Stack is NULL\n");

	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pop_top_node - Pops the top node from the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @ln: Line number of the opcode.
 */
void pop_top_node(stack_t **stack, unsigned int ln)
{
	stack_t *tmp;

	handle_error(stack == NULL || *stack == NULL,
			"Error: Stack underflow at line %u\n", ln);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * print_top_node - Prints the top node of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @ln: Line number of the opcode.
 */
void print_top_node(stack_t **stack, unsigned int ln)
{
	handle_error(stack == NULL || *stack == NULL,
			"Error: Stack is empty at line %u\n", ln);
	printf("%d\n", (*stack)->n);
}

/**
 * handle_error - Handles errors by printing an error message and exiting.
 * @condition: Condition to check for an error.
 * @format: Format string for the error message.
 * @...: Additional arguments for the format string.
 */
void handle_error(int condition, const char *format, ...)
{
	if (condition)
	{
		va_list args;

		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
		exit(EXIT_FAILURE);
	}
}
