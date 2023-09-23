#include "shell.h"

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 *
 * This function searches for an environment variable by name
 * and returns it * value as a string.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */

char *_getenv(char *name)
{
	int i;

	if (name == NULL)
		return (NULL);
	for (i = 0; environ[i] != NULL; i++)
	{
		char *variable = environ[i];

		if (_strncmp(variable, name, _strlen(name)) == 0)
		{
			char *value = _strchr(variable, '=');

			if (value != NULL)
				return (value + 1);
		}
	}
	return (NULL);
}

/**
 * print_env - Prints environment variable.
 *
 */

void print_env(void)
{
	int idx = 0;

	while (environ[idx] != NULL)
		e_printf("%s\n", environ[idx++]);
}

/**
 * _setenv - set variable as an environment variable.
 * @var: variable to be set
 * @val: value of var
 * @args: pointer to structs containing commands
 *
 * Return: On success - 0
 *          Otherwise - -1
 */

int _setenv(char *var, char *val, cmd_t *args)
{
	int i = 0, j;
	char new_var[1024];
	char **new_env;

	if (!var || !val)
		return (-1);

	_strcpy(new_var, var);
	_strcat(new_var, "=");
	_strcat(new_var, val);
	args->new_vars[args->var_count] = _strdup(new_var);

	for (; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], var, _strlen(var)) == 0)
		{
			environ[i] = args->new_vars[args->var_count];
			args->var_count++;
			args->called_setenv = 1;

			return (0);
		}
	}

	new_env = (char **)malloc((i + 3) * sizeof(char *));

	for (j = 0; environ[j] != NULL; j++)
		new_env[j] = environ[j];
	new_env[j] = args->new_vars[args->var_count];
	new_env[j + 1] = NULL;
	free(environ);
	environ = new_env;
	args->var_count++;
	args->called_setenv = 1;
	return (0);
}

/**
 * _unsetenv - Unset an environment variable
 * @var: variable to be unset
 *
 * Return: on sucess - 0
 *        Otherwise - -1
 */

int _unsetenv(char *var)
{
	int i = 0, size = 0, k = 0;
	char **temp;

	if (!var)
		return (-1);
	while (environ[size] != NULL)
		size++;
	temp = (char **)malloc((size + 1) * sizeof(char *));
	for (; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], var, _strlen(var)) != 0)
		{
			temp[k++] = environ[i];
		}
	}
	temp[k] = NULL;
	free(environ);
	environ = temp;
	return (0);
}

/**
 * copy_env - Copy environment variable.
 *
 */

void copy_env(void)
{
	char **new_env;
	int size = 0, i;

	while (environ[size] != NULL)
		size++;
	new_env = (char **)malloc((size + 1) * sizeof(char *));

	for (i = 0; i < size; i++)
		new_env[i] = environ[i];
	new_env[i] = NULL;
	environ = new_env;
}
