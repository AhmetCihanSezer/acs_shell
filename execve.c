#include "minishell.h"

int main(int argc, char const *argv[], char **env)
{
    char **arg;

    arg = malloc(sizeof(char *) * argc);
    int i = 1;
    while (i < argc)
    {
        arg[i-1] = strdup(argv[i]);
        i++;
    }
    arg[i-1] = NULL; 
    i = 0;
    while (arg[i])
    {
        printf("%s\n", arg[i]);
        i++;
    }
    execve(arg[0], arg, env);
    perror("Execve: ");
    return 0;
}
