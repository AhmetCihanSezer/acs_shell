#include "minishell.h"

void	free_darr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void del_data(void *content)
{
    free(((t_data *)content)->name);
    free(((t_data *)content)->value);
    free(content);
}

void built_in_exit(t_minishell *minishell)
{
    ft_lstclear(&(minishell->env), del_data);
    exit(NULL);
}
