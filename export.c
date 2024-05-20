#include "enviroment.h"

void ft_export(t_list *env)
{
    t_list *temp;

    temp = ft_cpylst(env);
    ft_sort_env(temp);
    while (temp->next)
    {
        printf("declare -x %s=\"%s\"\n", ((t_data *)temp->content)->title, ((t_data *)temp->content)->var);
        temp = temp->next;
    }
}

