#include "builtin.h"

static void set_pwd(t_list *head)
{
    while (head)
    {
        if (!ft_strncmp("PWD", ((t_data *)head->content)->name, 3))
            {
                free(((t_data *)head->content)->value);
                ((t_data *)head->content)->value = ft_strdup(pwd());
                break ;
            }
        head = head->next;
    }
}

int cd(char **arg, t_minishell *minishell) //add too many arguments
{
    t_list  *head;

    if (!*arg || !**arg)
        chdir("/");
    else 
    {
        if ((chdir(arg[0]) == -1))
            {
            perror("cd: ");
            return (0);
            }
    }
    set_pwd(minishell->env);
    return (1);
}

int main(int argc, char const *argv[], char **envp)
{
    // printf("%c", readline("> "));
    char *str;

    t_minishell minishell;
    t_list *head;
    minishell.env = set_env(envp);

    head = minishell.env;
    while (head)
    {
        if (!ft_strncmp("PWD", ((t_data *)head->content)->name, 3))
            {
                break ;
            }
        head = head->next;
    }

    while (1)
    {
        str = readline("> ");
        cd(&str, &minishell);
        printf("%s=%s\n", ((t_data *)head->content)->name, ((t_data *)head->content)->value);

    }

    return 0;
}
