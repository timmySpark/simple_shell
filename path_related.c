#include "shell.h"

/**
 * findPath - Determine if the given command can be executed.
 * @cmd: Command to be checked.
 * Return: Full path of the command or NULL if not found in PATH.
 */

char *findPath(char *cmd)
{
	char *environmentPath = _getenv("PATH");
	char *segment, *segmentCopy, *completePath, *envDuplicate = NULL;

	if (!environmentPath)
		return (NULL);

	envDuplicate = _strdup(environmentPath);

	segment = _strtok(envDuplicate, ":");
	while (segment)
	{
		segmentCopy = malloc(_strlen(segment) + _strlen(cmd) + 2);
		if (!segmentCopy)
		{
			perror("malloc");
			return (NULL);
		}
		segmentCopy = _strcpy(segmentCopy, segment);
		segmentCopy = _strcat(segmentCopy, "/");
		completePath = _strcat(segmentCopy, cmd);

		if (access(completePath, X_OK) == 0)
		{
			free(envDuplicate);
			return (completePath);
		}
		free(segmentCopy);
		segment = _strtok(NULL, ":");
	}
	free(envDuplicate);
	return (NULL);
}

/**
 * userInput - Prints a prompt, captures and returns user input.
 * @commands: Struct holding command data.
 * @arguments: Array of tokenized arguments.
 * Return: Pointer to the captured command string.
 */

char *userInput(cmd_t *commands, cmd_t *arguments)
{
	char *inputCopy;
	char *input = malloc(128);
	ssize_t readSize;
	int bufSize = 20;
	buff_t bufInfo;

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}

	bufInfo.index = 0;
	bufInfo.count = 0;
	readSize = _getline(&input, &bufSize, STDIN_FILENO, &bufInfo);

	if (readSize == 0)
	{
		free(input);
        free(commands);
        free(arguments);
		exit(0);
	}

	if (readSize == 1)
	{
		free(input);
		return (NULL);
	}

	if (input[readSize - 1] == '\n')
		input[readSize - 1] = '\0';
	input[readSize] = '\0';
	inputCopy = _strdup(input);

	free(input);
	return (inputCopy);
}

/**
 * runCommand - Initiates the command execution process.
 * @arguments: Array of arguments to pass.
 * @commands: Command-related data.
 * @cmdCount: Number of commands processed.
 * Return: Nothing.
 */


void runCommand(cmd_t *arguments, cmd_t *commands, int cmdCount)
{
	pid_t pid;
	int procStatus;
	int iter;

	pid = fork();
	if (pid == -1)
		perror("Forking process failed");

	if (pid == 0)
	{
		if (execve(arguments->args[0], arguments->args, environ) == -1)
			perror("Command execution failed");
	}
	else
	{
		wait(&procStatus);
		if (WEXITSTATUS(procStatus) != 0)
		{
			arguments->foundPath = 0;
		if (commands->arg_count == cmdCount && arguments->pipe)
			{
				free_cmd(arguments);
				free_cmd(commands);
				free(environ);
				exit(WEXITSTATUS(procStatus));
			}
		}
		for (iter = 0; arguments->args[iter]; iter++)
		{
			free(arguments->args[iter]);
			arguments->args[iter] = NULL;
		}
	}
}

/**
 * tokenize - Breaks down a command string into tokens.
 * @cmd: Command to tokenize.
 * @argumentsArr: Array to store tokenized strings.
 * @separator: Delimiter to use.
 * Return: Number of tokens, or -1 if "exit" command is issued.
 */


int tokenize(char *cmd, char *argumentsArr[], char *separator)
{
	int idx = 0;
	char *piece;

	piece = _strtok(cmd, separator);
	while (piece && idx < MAX_ARGS - 1)
	{
		argumentsArr[idx++] = _strdup(piece);
		piece = _strtok(NULL, separator);
	}
	argumentsArr[idx] = NULL;
	return (idx);
}

