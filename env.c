#include "builtin.h"

int ft_env(t_list *env)
{
    int i;

    if (!env)
        return (0);
    i = 0;
    while (env)
    {
        printf("%s\n", (char *) env->content);
        env = env->next;
    }
    return (1);
}
