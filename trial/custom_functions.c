#include "shell.h"

char is_delim(char str, char *delim){
    while (*delim)
    {
        if(str == *delim)
            return(1);
        delim++;
    }
    return (0);
}

/**
 * _strlen - a function that returns the length of a string
 * @str: character input str
 * Return: The length of str
 */

size_t _strlen(const char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}


char *_strtok(char *str, char *delim){
    static char *next_str;
    char *curr_str;

    if (!next_str)
        next_str = NULL;
    
    if (str == NULL)
        str = next_str;

    if (str == NULL)
        return (NULL);

    while (*str && is_delim(*str, delim))
        str++;
    
    if (*str == '\0'){
        next_str = NULL;
        return (NULL);
    }

    curr_str = str;

    while (*str && !is_delim(*str, delim))
        str++;

    if(*str){
        *str = '\0';
        next_str = str + 1;
    }
    else
        next_str = NULL;

    return (curr_str);
}

ssize_t _getline(char **line_ptr, size_t *n, FILE *stream){
    static char buffer[BUFFER_SIZE];
    static char *buf_ptr;
    static int chars_left;
    int char_count = 0;
    int fd = fileno(stream);

    if (!(*line_ptr))
    {
        *n = BUFFER_SIZE;
        *line_ptr = malloc(sizeof(char) * *n);

        if (!(*line_ptr))
           return(-1);

    }

    while (1)
    {
        if (chars_left <= 0)
        {
            chars_left = read(fd, buffer, BUFFER_SIZE);
            buf_ptr = buffer;

            if (chars_left <= 0)
            {
                if (char_count == 0){
                    return(-1);
                }
                break;

            }
        }

        if (char_count + 1 > *n)
        {
            *n += BUFFER_SIZE;
            *line_ptr = realloc(*line_ptr, *n);

            if(!(*line_ptr))
                return (-1);
        }

        if (*buf_ptr == '\n')
        {
            (*line_ptr)[char_count++] = '\0';
            buf_ptr++;
            chars_left--;
            return(char_count);
        }

        (*line_ptr)[char_count++] = *buf_ptr++;
        chars_left--;

    }

   (*line_ptr)[char_count] = '\0';
    return (char_count);

}

void cd_command(char **args) {
    char *directory = args[1];

    if (!directory || strcmp(directory, "~") == 0) {
        directory = getenv("HOME");
    } else if (strcmp(directory, "-") == 0) {
        directory = getenv("OLDPWD");
    }

    if (chdir(directory) != 0) {
        perror("cd");
        return;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    } else {
        perror("getcwd");
    }
}


