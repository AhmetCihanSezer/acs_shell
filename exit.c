#include "builtin.h"

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

void    del_data(t_data* data)
{
    free(data->name);
    free(data->value);
    free(data);
}

void built_in_exit(t_minishell *minishell)
{
    ft_lstclear(&(minishell->env), del_data);
    exit(NULL);
}
