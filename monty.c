#include "monty.h"

Stack stack;

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
