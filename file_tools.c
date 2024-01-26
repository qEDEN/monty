#include "monty.h"

/**
 * process_file - Processes the Monty bytecode file.
 * @file_name: The file namepath.
 * Return: void
 */
void process_file(char *file_name)
{
	int line_number = 1, format = 0;
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		err(2, file_name);

	char *buffer = NULL;
	size_t len = 0;

	while (getline(&buffer, &len, fd) != -1)
	{
		format = parse_line(buffer, line_number, format);
		line_number++;
	}

	fclose(fd);
	free(buffer);
}

/**
 * parse_line_and_execute - Parses a line & executes the corresponding op.
 * @buffer: Line from the file.
 * @line_number: Line number.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 * Return: void
 */
void parse_line_and_execute(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return;

	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		format = 0;
	else if (strcmp(opcode, "queue") == 0)
		format = 1;
	else
		find_and_execute(opcode, value, line_number, format);
}

/**
 * find_and_execute - Finds and executes the function for the opcode.
 * @opcode: Opcode.
 * @value: Argument of opcode.
 * @line_number: Line number.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 * Return: void
 */
void find_and_execute(char *opcode, char *value, int line_number, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_function(func_list[i].f, opcode, value, line_number, format);
			flag = 0;
		}
	}

	if (flag == 1)
		err(3, line_number, opcode);
}

/**
 * call_function - Calls the required function based on the opcode.
 * @func: Pointer to the function that is about to be called.
 * @opcode: String representing the opcode.
 * @value: String representing a numeric value.
 * @ln: Line number for the instruction.
 * @format: Format specifier. If 0, nodes will be entered as a stack.
 * Return: void
 */
void call_function(op_func func, char *opcode, char *value, int ln, int format)
{
	stack_t *node;
	int flag;

	flag = 1;
	if (strcmp(opcode, "push") == 0)
	{
		if (value != NULL && value[0] == '-')
		{
			value = value + 1;
			flag = -1;
		}

		if (value == NULL || !isdigit_str(value))
			err(5, ln);

		node = create_node(atoi(value) * flag);

		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_to_queue(&node, ln);
	}
	else
		func(&head, ln);
}

/**
 * isdigit_str - Checks if a string consists of digits.
 * @str: String to check.
 * Return: 1 if all characters are digits, 0 otherwise.
 */
int isdigit_str(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
			return (0);
	}

	return (1);
}
