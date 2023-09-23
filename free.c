#include "shell.h"

void free_cmd(cmd_t *cmd)
{
    int i;

    for (i = 0; i < cmd->arg_count; i++)
        free(cmd->args[i]);
    if (cmd->called_setenv)
    {
        for (i = 0; i < cmd->var_count; i++)
            free(cmd->new_vars[i]);
    }
    free(cmd);
}


/**
 * free_args - Frees argument vector
 * @args: Vector to free
 * @num_token: Number of tokens in vector
 *
 * Return: Nothing
 */
void free_args(char *args[], int num_token)
{
	int i;

	for (i = 0; i < num_token; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
}

