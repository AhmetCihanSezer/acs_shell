#include "minishell.h"

// int main(int argc, char const *argv[], char **env)
// {
//     char **arg;

//     arg = malloc(sizeof(char *) * argc);
//     int i = 1;
//     while (i < argc)
//     {
//         arg[i-1] = strdup(argv[i]);
//         i++;
//     }
//     arg[i-1] = NULL; 
//     i = 0;
//     while (arg[i])
//     {
//         printf("%s\n", arg[i]);
//         i++;
//     }
//     execve(arg[0], arg, env);
//     perror("Execve: ");
//     return 0;
// }

// cat <merhaba.txt | grep | wc
int main(int argc, char const *argv[], char **env)
{
    t_minishell mini;
    mini.env_arr = env;
    t_command *cmd = malloc(sizeof(t_command));
    char *arg1[] = {"cat"};
    cmd->arg = arg1;
    printf("%s\n", argv[0]);
}
