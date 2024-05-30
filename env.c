#include "builtin.h"

int env(t_list *env)
{
    int i;

    if (!env)
        return (0);
    i = 0;
    while (env)
    {
        printf("%s = %s \n", ((t_data *)env->content)->name,((t_data *)env->content)->value);
        env = env->next;
    }
    return (1);
}
