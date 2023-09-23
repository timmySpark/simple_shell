#include "main.h"

/**
 * check_hash - Check if a command is a hash-bang executable.
 * @cmd: The command to check.
 *
 * This function checks if the given command is a hash-bang executable
 * (starts with '#!'). If it is, it returns 1; otherwise, it returns 0.
 *
 * Return: 1 if the command is a hash-bang executable, 0 otherwise.
 */
int check_hash(char *cmd)
{
	if (cmd != NULL && cmd[0] == '#' && cmd[1] == '!')
		return (1);
	return (0);
}

/**
 * tokenize_cmd - Tokenize a command string.
 * @cmd: The command string to tokenize.
 *
 * This function tokenizes the given command string into an array of tokens,
 * splitting it based on whitespace characters.
 *
 * Return: An array of tokens (strings) or NULL on failure.
 */
char **tokenize_cmd(char *cmd)
{
	int i, num_tokens = 0;
	char **tokens = NULL;
	char *token, *token_cpy;

	if (cmd == NULL)
		return (NULL);

	/* Count the number of tokens (words) in the command */
	token = strtok(cmd, " \t\r\n");
	while (token != NULL)
	{
		num_tokens++;
		token = strtok(NULL, " \t\r\n");
	}

	if (num_tokens == 0)
		return (NULL);

	/* Allocate memory for the token array */
	tokens = malloc((num_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	/* Copy tokens into the array */
	token = strtok(cmd, " \t\r\n");
	for (i = 0; i < num_tokens; i++)
	{
		token_cpy = strdup(token);
		if (token_cpy == NULL)
		{
			free(tokens);
			return (NULL);
		}
		tokens[i] = token_cpy;
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * cl_exec - Execute a command.
 * @cmd: The command to execute.
 *
 * This function executes the given command by forking a child process and
 * using the `execve` system call. It waits for the child process to complete
 * before returning.
 */
void cl_exec(char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
		perror("fork failed");
	if (child_pid == 0)
	{
		char **args = tokenize_cmd(cmd);
		if (args != NULL)
		{
			if (execvp(args[0], args) == -1)
				perror("execvp");
			free(args);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

/**
 * read - Read input from the user.
 * @prompt: The prompt to display to the user.
 *
 * This function displays the given prompt to the user and reads a line of
 * input from the standard input. It returns the input as a dynamically
 * allocated string.
 *
 * Return: A dynamically allocated string containing the user's input,
 * or NULL on failure.
 */
char *read(const char *prompt)
{
    char *input = NULL;
    size_t input_size = 0;

    if (prompt != NULL)
        printf("%s", prompt);

    ssize_t bytes_read = getline(&input, &input_size, stdin);

    if (bytes_read == -1)
    {
        perror("getline");
        free(input);
        return NULL;
    }

    // Remove newline character if present
    if (bytes_read > 0 && input[bytes_read - 1] == '\n')
        input[bytes_read - 1] = '\0';

    return input;
}

