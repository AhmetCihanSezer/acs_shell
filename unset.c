#include "enviroment.h"

void ft_del_content(void *content)
{
    free(((t_data *)content)->title);
    free(((t_data *)content)->var);
}

void ft_unset(t_list *env, char *arg)
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