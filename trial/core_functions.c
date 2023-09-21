#include "shell.h"


char *substitute_var(char *token) {
    if (token[0] == '$') {
        char *value = getenv(token + 1);  // +1 to skip the $
        if (value) {
            return value;
        }
    }
    return token;
}

char *read_line(char *name){
    char *line = NULL;
    size_t buf = BUFFER_SIZE;

    if(_getline(&line , &buf , stdin) == -1){
        if (feof(stdin)){
            free(line);
            exit(EXIT_SUCCESS);
        }
        else
        {
            free(line);
            perror(name);
            exit(EXIT_FAILURE);
            
        }
    }
    return (line);    
}

char **split_line(char *line, char * name){
    int i = 0, bufsize = BUFFER_SIZE;
    char *str;
    char **tokens;

    tokens = malloc(sizeof(char) * bufsize);

    if (!tokens){
        perror(name);
        exit(EXIT_FAILURE);

    }    

    str = _strtok(line, TOKEN_DELIM);

    while (str != NULL)
    {
        if (str[0] == '#') { 
            break;
        }
        tokens[i] = str;
        i++;

        if (i >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, sizeof(char *) * bufsize);
            if (!tokens)
            {
                perror(name);
                exit(EXIT_FAILURE);
            }
        }

        str = _strtok( NULL, TOKEN_DELIM);
    }

    tokens[i] = NULL;
    return(tokens);
}


void run_command(char **args, char *name) {
    pid_t pid, wpid;
    int status;
    extern char **environ;

    for (int i = 0; args[i]; i++) {
        args[i] = substitute_var(args[i]);
    }

    char *cmd_path = find_command(args[0]);
    if (!cmd_path) {
        fprintf(stderr, "%s: Command not found: %s\n", name, args[0]);
        return;
    }

    pid = fork();

    if (pid == 0) {
        if (execve(cmd_path, args, environ) == -1) {
            perror(name);
            free(cmd_path);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror(name);
        free(cmd_path);
        exit(EXIT_FAILURE);
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    free(cmd_path);
}


/*
char *find_command(const char *command) {
    char *path = getenv("PATH");
    char *path_copy, *token , *full_path; 
    
    if (!path)
        return NULL;

    path_copy = strdup(path);
    if (!path_copy) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    token = _strtok(path_copy, ":");
    
    while (token != NULL) {
        full_path = malloc(_strlen(token) + _strlen(command) + 2);
        
        if (!full_path) {
            perror("malloc");
            free(path_copy);
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        token = _strtok(NULL, ":");
    }

    free(path_copy);  
    return (NULL);
}
*/


char *find_command(const char *command) {
    if (command[0] == '/') {
        return strdup(command);
    }

    const char *path_orig = getenv("PATH");
    char *path = strdup(path_orig);
    char *token, *full_path;

    if (!path_orig) {
        free(path);
        return NULL;
    }
    
    if (!path) {
        return NULL;
    }

    token = _strtok(path, ":");

    while (token != NULL) {
        full_path = malloc(_strlen(token) + _strlen(command) + 2);

        if (full_path == NULL) {
            perror("malloc");
            free(path);
            return NULL;
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            free(path);
            return full_path;
        }

        free(full_path);
        token = _strtok(NULL, ":");
    }
    free(path);
    return (NULL);
}








/*
int run_command(char **args, char *name){
    pid_t pid;
    int status;

    char *exvp[] = {NULL};
    char *command_path = args[0];

    if (access(command_path, F_OK) != 0) {
        command_path = find_command(args[0]);
        if (!command_path) {
            fprintf(stderr, "%s: Command not found in PATH: %s\n", name, args[0]);
            return -1;
        }
    }

    pid = fork();

    if (pid == 0) {
        if (execve(command_path, args, exvp) == -1) {
            perror(name);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            fprintf(stderr, "Child Process did not exit normally\n");
            return (-1);
        }
    } else {
        perror(name);
        return (-1);
    }
}

void run_command(char **args, char * name){
    pid_t pid , wpid;
    int status;
    extern char **environ;


    pid =  fork();

    if (pid == 0){
        if(execve(args[0], args, environ) == -1)
        {
            perror(name);
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0){
        perror("Shell Failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        while (1)
        {
            wpid = waitpid(pid, &status, 0);

            if (WIFEXITED(status) || WIFSIGNALED(status))
            {
                break;
            }
        }
    } 
}

char *find_command(const char *command)
{
    const char *path_orig = getenv("PATH");
    char *path = strdup(path_orig);
    char *token, *full_path;
    
    if (!path_orig) {
        return NULL;
    }
    
    if (!path) {
        return NULL;
    }
    

    token = _strtok(path, ":");

    while (token != NULL) {
        full_path = malloc(_strlen(token) + _strlen(command) + 2);
        
        if (full_path == NULL) {
            perror("malloc");
            free(full_path);
            return NULL;
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (access(full_path, X_OK) == 0) {
            free(path);
            return (full_path);
        }

        free(full_path);
    }
    free(path);
    return (NULL);
}
*/
