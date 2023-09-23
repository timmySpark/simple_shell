#include "main.h"
#include "eprintf.h"

/**
 * looper - Handles command execution.
 * @cmmds: Struct holding information of commands separated by ";"
 * @args: Struct holding information of commands.
 * @argv_0: Name of program held in argv[0].
 * @cmd_count: Pointer to number of commands executed.
 *
 * Return: Nothing.
 */
void looper(cmd_t *cmmds, cmd_t *args, char *argv_0, int *cmd_count)
{
    int i;

    for (i = 0; i < cmmds->arg_count; i++)
    {
        cmmds->args[i] = rmv_space(cmmds->args[i]);
        cmmds->args[i] = check_hash(cmmds->args[i]);
        if (cmmds->args[i] == NULL)
            continue;
        args->arg_count = tokenize_cmd(cmmds->args[i], args->args, " ");
        if (sCases(cmmds, args, *cmd_count, i, argv_0))
        {
            free(cmmds->args[i]);
            (*cmd_count)++;
            continue;
        }
        cl_exec(cmmds, args, *cmd_count, argv_0);
        free(cmmds->args[i]);
        (*cmd_count)++;
    }
}

/**
 * init_cmd_t - Initializes cmd_t struct.
 *
 * This function initializes a cmd_t object that will be used in the main program.
 *
 * Return: Initialized cmd_t object
 */
cmd_t *init_cmd_t()
{
    cmd_t *cmmds;

    cmmds = (cmd_t *)malloc(sizeof(cmd_t));
    if (!cmmds)
        perror("malloc - cmmds");
    cmmds->arg_count = 0;
    cmmds->piped = false;
    cmmds->foundPath = true;
    cmmds->called_setenv = false;
    return (cmmds);
}

/**
 * read_file - Reads a file.
 * @input_file: Name of file.
 * @argv_0: Name of the program, held in argv[0].
 * @cmmds: Pointer to struct containing commands information.
 * @args: Pointer to struct containing commands information.
 *
 * Return: Copy of buffer containing file content.
 */
char *read_file(char *input_file, char *argv_0, cmd_t *cmmds, cmd_t *args)
{
    int file;
    char buff[1024];
    ssize_t bytesRead, tBytesRead = 0;

    if (input_file == NULL)
    {
        e_printf("%s is null", input_file);
        exit(errno);
    }

    file = open(input_file, O_RDONLY);
    if (file == -1)
    {
        e_printf("%s: 0: Can't open %s\n", argv_0, input_file);
        args->foundPath = false;
        cleanup(cmmds, args);
    }
    buff[0] = '\0';
    while (1)
    {
        bytesRead = read(file, buff, sizeof(buff));
        tBytesRead += bytesRead;
        if (bytesRead == 0)
            break;
        if (bytesRead == -1 || file == -1)
        {
            e_printf("%s: 0: cannot read %s\n", argv_0, input_file);
            args->foundPath = false;
            cleanup(cmmds, args);
        }
    }
    buff[tBytesRead] = '\0';
    if (close(file) == -1)
    {
        e_printf("%s: 0: cannot close %s\n", argv_0, input_file);
        args->foundPath = false;
        cleanup(cmmds, args);
    }
    return (_strdup(buff));
}

/**
 * replace_char - Replaces a character in a string.
 * @str: Input string.
 * @c: Character to replace.
 * @s: Character to replace @c.
 *
 * Return: Pointer to corrected string.
 */
char *replace_char(char *str, char c, char s)
{
    int i, j = 0;
    char *new_str;

    if (!str || str == NULL)
        return (NULL);

    new_str = malloc(_strlen(str) + 1);
    if (!new_str)
        return (NULL);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
            str[i] = s;
        new_str[j++] = str[i];
    }
    new_str[j] = '\0';
    free(str);
    return (new_str);
}

/**
 * rmv_double - Removes occurrences of double character @c in input string @cmd.
 * @cmd: Input string.
 * @c: Double character to remove.
 *
 * Return: Pointer to corrected string.
 */
char *rmv_double(char *cmd, char c)
{
    int i, j = 0;
    char *cmd_clean;
    bool prev_space = (cmd[0] == c);

    cmd_clean = malloc(_strlen(cmd) + 1);

    for (i = 0; cmd[i] != '\0'; i++)
    {
        if (cmd[i] == c)
        {
            if (!prev_space)
                cmd_clean[j++] = cmd[i];
            prev_space = true;
        }
        else
        {
            cmd_clean[j++] = cmd[i];
            prev_space = false;
        }
    }
    cmd_clean[j] = '\0';
    free(cmd);
    cmd = cmd_clean;
    return (cmd);
}

