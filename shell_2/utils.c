#include "main.h"

char *_getenv(char *name) {
    int i;

    if (name == NULL)
        return (NULL);
    for (i = 0; environ[i] != NULL; i++) {
        char *variable = environ[i];

        if (_strncmp(variable, name, _strlen(name)) == 0) {
            char *value = _strchr(variable, '=');

            if (value != NULL)
                return (value + 1);
        }
    }
    return (NULL);
}

int _strlen(char *c) {
    int len = 0;

    if (c == NULL)
        return (-1);
    while (c[len] != '\0')
        len++;
    return (len);
}

int _strncmp(char *s1, char *s2, int n) {
    int i;

    if ((s1 == NULL) || (s2 == NULL))
        return (-1);
    for (i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return (1);
    }
    return (0);
}

char *_strchr(char *s, char c) {
    if ((s == NULL) || !c)
        return (NULL);
    while (*s != '\0') {
        if (*s == c)
            return (s);
        s++;
    }
    return (NULL);
}

char *_strdup(char *s) {
    char *dup = NULL;
    int i;
    int len;

    if (s == NULL)
        return (NULL);
    len = _strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);

    for (i = 0; i < len; i++)
        dup[i] = s[i];
    dup[i] = '\0';
    return (dup);
}

ssize_t _getline(char **lineptr, int *n, int fd, buff_t *buf) {
    char c;
    ssize_t tBytesRead = 0, bufferResult = 0;

    if (!lineptr || !n || !buf)
        return (-1);
    if (*lineptr == NULL || *n < 2) {
        *n = 64;
        *lineptr = (char *)malloc(*n);
        if (!(*lineptr))
            return (-1);
    }
    while (1) {
        if (tBytesRead >= (*n) - 2) {
            (*n) *= 2;
            *lineptr = _realloc(lineptr, *n, tBytesRead);
        }
        bufferResult = read_buffer(fd, buf);
        if (bufferResult < 0)
            return (-1);
        else if (bufferResult == 0 && tBytesRead == 0)
            return (0);
        else if (bufferResult == 0)
            break;
        c = buf->data[buf->index++];
        (*lineptr)[tBytesRead++] = c;
        if (c == '\n' && !(isatty(STDIN_FILENO) == 0))
            break;
    }
    (*lineptr)[tBytesRead] = '\0';
    return (tBytesRead);
}

char *_strcat(char *dest, char *src) {
    int i;
    size_t len;

    if (dest == NULL || src == NULL)
        return (NULL);

    len = _strlen(dest);

    for (i = 0; src[i] != '\0'; i++)
        dest[len++] = src[i];
    dest[len] = '\0';

    return (dest);
}

char *_strtok(char *str, char *delim) {
    static char *next_token;
    char *token_start = NULL;
    bool found_delim = false;

    if (str != NULL)
        next_token = str;

    token_start = next_token;

    while (next_token && *next_token != '\0') {
        if (_strchr(delim, *next_token) != NULL) {
            *next_token = '\0';
            next_token++;
            found_delim = true;
            break;
        }
        next_token++;
    }

    if (found_delim || *token_start != '\0')
        return (token_start);
    else
        return (NULL);
}

char *_strcpy(char *dest, char *src) {
    size_t i;
    size_t len;

    if (!src)
        return (NULL);

    len = _strlen(src);

    for (i = 0; i < len; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

ssize_t read_buffer(int fd, buff_t *buf) {
    if (buf->index >= buf->count) {
        buf->count = read(fd, buf->data, BUFFER_SIZE);
        if (buf->count <= 0)
            return (buf->count);
        buf->index = 0;
    }
    return (buf->count);
}

char *checkPath(char *cmd) {
    char *envir = _getenv("PATH");
    char *token, *token_cpy, *full_path, *env_cpy = NULL;

    if (envir == NULL)
        return (NULL);
    env_cpy = _strdup(envir);

    token = _strtok(env_cpy, ":");
    while (token != NULL) {
        token_cpy = malloc(_strlen(token) + _strlen(cmd) + 2);
        if (!token_cpy) {
            perror("malloc");
            return (NULL);
        }
        token_cpy = _strcpy(token_cpy, token);
        token_cpy = _strcat(token_cpy, "/");
        full_path = _strcat(token_cpy, cmd);
        if (access(full_path, X_OK) == 0) {
            free(env_cpy);
            env_cpy = NULL;
            return (full_path);
        } else {
            free(token_cpy);
            token_cpy = NULL;
            token = _strtok(NULL, ":");
        }
    }
    free(env_cpy);
    env_cpy = NULL;
    return (NULL);
}

char *getPrompt() {
    char *c_cpy;
    char *c = malloc(128);
    ssize_t i;
    int n = 20;
    buff_t buf;

    if (isatty(STDIN_FILENO)) {
        write(STDOUT_FILENO, "$ ", 2);
        fflush(stdout);
    }

    buf.index = 0;
    buf.count = 0;
    i = _getline(&c, &n, STDIN_FILENO, &buf);
    if (i == 0) {
        free(c);
        exit(0);
    }
    if (i == 1) {
        free(c);
        return (NULL);
    }

    if (c != NULL) {
        if (c[i - 1] == '\n')
            c[i - 1] = '\0';
        c[i] = '\0';
        c_cpy = _strdup(c);
	if (!c_cpy)
		perror("strdup error");
    }

    free (c);
    return (c_cpy);
}

