#include "shell.h"

/**
 * cases - Handles special commands.
 *@cmds: Commands.
 *@args: Arguments.
 *@cmd_count: Number of commands executed.
 *@i: ith command in cmds.
 *@argv: Name of program held in argv[0].
 * Return: 1 if any special commands.
 */

int cases(cmd_t *cmds, cmd_t *args, int cmd_count, int i, char *argv)
{
    char *cmd_name = args->args[0];
    size_t j = 0;

    scases_t commands[] = {
        {"setenv", _setenv_cmd},
        {"unsetenv", _unsetenv_cmd},
        {"exit", _exit_cmd},
        {"env", _env_cmd},
        {"cd", cd_cmd},
    };
    for (j = 0; j < sizeof(commands) / sizeof(commands[0]); j++)
    {
        if (_strncmp(cmd_name, commands[j].name, _strlen(commands[j].name)) == 0)
            return (commands[j].func(args, cmds, cmd_count, i, argv));
    }
    return (0);
}

int _setenv_cmd(cmd_t *args, cmd_t *cmds, int cmd_count, int i, char *argv)
{
    int state = _setenv(args->args[1], args->args[2], args);

    (void)cmds;
    (void)cmd_count;
    (void)i;
    (void)argv;
    if (state == -1)
        perror("_setenv");
    free_args(args->args, args->arg_count);
    return (1);
}

int _unsetenv_cmd(cmd_t *args, cmd_t *cmds, int cmd_count, int i, char *argv)
{
    int state = _unsetenv(args->args[1]);

    (void)cmds;
    (void)cmd_count;
    (void)i;
    (void)argv;
    if (state == -1)
        perror("_unsetenv");
    free_args(args->args, args->arg_count);
    return (1);
}

int _exit_cmd(cmd_t *args, cmd_t *cmds, int cmd_count, int i, char *argv)
{
    _exits(cmds, args, cmd_count, i, argv);
    return (1);
}

int _env_cmd(cmd_t *args, cmd_t *cmds, int cmd_count, int i, char *argv)
{
    (void)cmds;
    (void)cmd_count;
    (void)i;
    (void)argv;
    (void)args;
    print_env();
    free_args(args->args, args->arg_count);
    return (1);
}


