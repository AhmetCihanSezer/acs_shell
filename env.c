#include "minishell.h"

void	env(t_list *env)
{
	if (!env)
		exit(125);
	while (env)
	{
		if (!(((t_env *)env->content)->key))
			printf("%s=%s\n", ((t_env *)env->content)->name,((t_env *)env->content)->key);
		env = env->next;
	}
	exit(0);
}
