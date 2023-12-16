#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

/**
 * struct Stack - A simple stack structure.
 * @stack: An array to store stack elements.
 * @top: The index of the top element in the stack.
 */
typedef struct Stack {
    int stack[STACK_SIZE];
    int top;
} Stack;

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

/**
 * main - The main function of the Monty interpreter.
 * @argc: The number of command line arguments.
 * @argv: An array of strings containing the command line arguments.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;

        char *opcode = strtok(line, " \n");

        if (opcode != NULL)
        {
            if (strcmp(opcode, "push") == 0)
            {
                char *value_str = strtok(NULL, " \n");
                if (value_str == NULL)
                {
                    fprintf(stderr, "L%d: usage: push integer\n", line_number);
                    exit(EXIT_FAILURE);
                }

                int value = atoi(value_str);
                push(value);
            }
            else if (strcmp(opcode, "pall") == 0)
            {
                pall();
            }
            else
            {
                fprintf(stderr, "L%d: unknown opcode %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
}
