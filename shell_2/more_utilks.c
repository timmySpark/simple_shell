#include "main.h"

/**
 * cleanup - Clean up resources and free memory.
 * @cmd: The command structure to clean up.
 *
 * This function frees memory allocated for a command structure.
 */
void cleanup(cmd_t *cmd)
{
    if (cmd == NULL)
        return;

    if (cmd->args != NULL)
    {
        free_args(cmd->args);
        cmd->args = NULL;
    }

    if (cmd->path != NULL)
    {
        free(cmd->path);
        cmd->path = NULL;
    }
}

/**
 * free_args - Free memory allocated for an array of command arguments.
 * @args: The array of arguments to free.
 */
void free_args(char **args)
{
    if (args == NULL)
        return;

    for (int i = 0; args[i] != NULL; i++)
    {
        free(args[i]);
    }

    free(args);
}

/**
 * _ext - Placeholder function with a specific purpose.
 *
 * This function serves a specific purpose based on your application.
 * You should implement the functionality as needed for your program.
 */
void _ext()
{
    // Implement the specific functionality here.
}

/**
 * print_env - Print the environment variables.
 */
void print_env()
{
    for (char **env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

