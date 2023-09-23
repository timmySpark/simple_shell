#include "shell.h"

/**
 * main - This is the entry point of a custom UNIX command line interpreter
 * @argc: Argument count
 * @argv: Arguments vector
 *
 * Return: 0 on success
 */

int main(int argc, char *argv[])
{
	int cmd_count = 1;
	char *cmd;
	cmd_t *cmmds, *args;

	copy_env();
	cmmds = init_cmd_t();
	args = init_cmd_t();
	args->var_count = 0;
	while (!args->pipe)
	{
		if (argc == 2)
		{
			cmd = read_file(argv[1], argv[0], cmmds, args);
			cmd = replace_char(cmd, '\n', ';');
			cmd = rmv_double(cmd, ';');
			args->pipe = 1;
		}
		else
			cmd = userInput(cmmds, args);
		if (isatty(STDIN_FILENO) == 0)
		{
			args->pipe = 1;
		}
		if (cmd == NULL)
		{
			cmd_count++;
			continue;
		}
		cmd = rmv_space(cmd);
		cmd = replace_char(cmd, '\n', ';');
		cmd = rmv_double(cmd, ';');
		cmmds->arg_count = tokenize(cmd, cmmds->args, ";");
		free(cmd);
		looper(cmmds, args, argv[0], &cmd_count);
	}
	clean(cmmds, args);
	return (0);
}

