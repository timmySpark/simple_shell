#include "shell.h"


void interactive_shell(char **envp, char *name){
    char *line;
    char **args;
    int status;

    while (1){
        printf("#shellO$ ");
        fflush(stdout);

        line = read_line(name);

        if (!line)
        {
            free(line);
            continue;
        }

        args = split_line(line, name);

        if (args[0] == NULL) {
            free(line);
            free(args);
            continue;
        }
        if (args[0] != NULL && strcmp(args[0], "setenv") == 0)
			_setenv(args);
		else if (args[0] != NULL && strcmp(args[0], "unsetenv") == 0)
			_unsetenv(args);
		else if (args[0] != NULL && strcmp(args[0], "env") == 0)
			print_environment(envp);
		else if (args[0] != NULL && strcmp(args[0], "exit") == 0)
		{
			if (args[1] != NULL)
			{
				status = atoi(args[1]);
				free(line);
				free(args);
				exit(status);
			}
			else
			{
				free(line);
				free(args);
				exit(EXIT_SUCCESS);
			}
		}
        if (strcmp(args[0], "cd") == 0) {
            cd_command(args);
        } else {
            run_command(args, name);
        }
        free (line);
        free(args);
        
    }
}

void not_interactive_shell(char *name) {
    char *line;
    char **args;

    while (1){
        line = read_line(name);

        if (!line)
            break;

        args = split_line(line, name);
        
        if (args && args[0]) {
            run_command(args, name);
        }

        free(line);
        free(args);
    }
}

