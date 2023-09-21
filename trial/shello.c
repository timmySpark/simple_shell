#include "shell.h"

int  main(int argc, char *argv[], char *envp[]){
    (void) argc;

    if (isatty(STDIN_FILENO) == 1){
        interactive_shell(envp,argv[0]);
    }
    else
    {
        not_interactive_shell(argv[0]);
    }
    
}

