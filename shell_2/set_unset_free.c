#include "main.h"

/**
 * _setenv - Sets @variable as an environment variable wih value @value
 * @variable: Variable to set.
 * @value: Value of @variable
 * @args: Pointer to struct containing commands information.
 * Return: 0 if success, -1 if fail.
 */
int _setenv(char *variable, char *value, cmd_t *args)
{
    int i = 0, j;
    char new_var[1024];
    char **new_env;

    if (!variable || !value)
        return (-1);

    _strcpy(new_var, variable);
    _strcat(new_var, "=");
    _strcat(new_var, value);
    args->new_vars[args->n_var_count] = _strdup(new_var);
    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(environ[i], variable, _strlen(variable)) == 0)
        {
            environ[i] = args->new_vars[args->n_var_count];
            args->n_var_count += 1;
            args->called_setenv = true;
            return (0);
        }
    }
    new_env = (char **)malloc((i + 3) * sizeof(char *));
    for (j = 0; environ[j] != NULL; j++)
        new_env[j] = environ[j];
    new_env[j] = args->new_vars[args->n_var_count];
    new_env[j + 1] = NULL;
    free(environ);
    environ = new_env;
    args->n_var_count += 1;
    args->called_setenv = true;
    return (0);
}

/**
 * _unsetenv - Unsets an environment variable
 * @variable: Variable to unset
 * Return: 0 on success, -1 on fail.
 */
int _unsetenv(char *variable)
{
    int i = 0, size = 0, k = 0;
    char **temp;

    if (variable == NULL || !variable)
        return (-1);
    while (environ[size] != NULL)
        size++;
    temp = (char **)malloc((size + 1) * sizeof(char *));
    for (i = 0; environ[i] != NULL; i++)
    {
        if (_strncmp(environ[i], variable, _strlen(variable)) != 0)
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
 * copy_env - Copies environment variables.
 *
 * Return: Nothing.
 */
void copy_env(void)
{
    char **new_env;
    int size = 0, i;

    while (environ[size] != NULL)
        size++;
    new_env = (char **)malloc((size + 1) * (sizeof(char *)));
    for (i = 0; i < size; i++)
        new_env[i] = environ[i];
    new_env[i] = NULL;
    environ = new_env;
}

/**
 * free_cmd_t - Frees cmd_t struct
 * @cmmd: Struct to free
 *
 * Return: Nothing.
 */
void free_cmd_t(cmd_t *cmmd)
{
    int i;

    for (i = 0; i < cmmd->arg_count; i++)
    {
        free(cmmd->args[i]);
    }
    if (cmmd->called_setenv)
    {
        for (i = 0; i < cmmd->n_var_count; i++)
        {
            free(cmmd->new_vars[i]);
        }
    }

    free(cmmd);
}

