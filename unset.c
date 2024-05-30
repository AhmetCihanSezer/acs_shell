#include "minishell.h"

void ft_del_content(void *content)
{
    free(((t_data *)content)->name);
    free(((t_data *)content)->value);
    free(content);
}

void ft_unset(char **arg, t_minishell *minishell)
{
    t_list  *env;
    int i;

    if (!arg[0])
        return ;
    i = 0;
    while (arg[i])
    {
        env = minishell->env;
        while (env)
        {
            if (!ft_strncmp(((t_data *)env->content)->name, arg, ft_strlen(arg)))
                ft_lstdelone(env, ft_del_content);
            env = env->next;
        }
        i++;
    }
    
}
