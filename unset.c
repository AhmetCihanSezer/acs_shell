#include "enviroment.h"

void ft_del_content(void *content)
{
    free(((t_data *)content)->name);
    free(((t_data *)content)->value);
}

void ft_unset(char **arg, t_minishell *minishell)
{
    
    if (!arg)
        return ;
    while (env)
    {
        if (!strcmp(((t_data *)env->content)->title, arg))
            ft_lstdelone(env, ft_del_content);
        env = env->next;
    }
}
