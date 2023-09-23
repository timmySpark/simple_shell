#include "shell.h"

/**
 * check_hash - Check for comments in a string
 * @str: The input string
 *
 * Return: A new string without comments,
 * or the original input string if '#' is in a word.
 */
char *check_hash(char *str)
{
	int i, index = 0;
	int len = _strlen(str);
	char *hash = NULL;

	if (str[0] == '#')
	{
		free(str);
		return (NULL);
	}

	for (i = 1; i < len; i++)
	{
		if (str[i] == '#' && (str[i - 1] == ' ' || str[i - 1] == '\t'))
		{
			index = i - 1;
			break;
		}
	}

	if (index > 0)
	{
		hash = (char *)malloc(index + 1);
		for (i = 0; i < index; i++)
			hash[i] = str[i];
		hash[index] = '\0';

		free(str);
		return (hash);
	}
	else
		return (str);
}

/**
 *cd_cmd - Handles cd command.
 *@cmmds: cmmds
 *@args: args
 *@cmd_count: Number of commands executed.
 *@i: ith command in cmmds.
 *@argv_0: Name of program held in argv[0].
 *Return: 1
 */

int cd_cmd(cmd_t *args, cmd_t *cmmds, int cmd_count, int i, char *argv_0)
{
	(void)cmmds;
	(void)i;
	cd(args, argv_0, cmd_count);
	args->called_setenv = 1;
	free_args(args->args, args->arg_count);
	return (1);
}

