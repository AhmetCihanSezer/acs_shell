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

void	del_env(void *content)
{
    free(((t_env *)content)->name);
    free(((t_env *)content)->key);
    free(content);
}

void	del_token(void	*content)
{
	free(((t_token *)content)->value);
	free(content);
}

void	del_command(void	*content)
{
	free(((t_command *)content)->arg);
	ft_lstclear(&(((t_command *)content)->infile_list), del_token);
	ft_lstclear(&(((t_command *)content)->outfile_list), del_token);
}

void	built_in_exit(t_minishell *mini)
{
	write(1,"a\n", 2);
	ft_lstclear(&(mini->token_list), del_token);
    ft_lstclear(&(mini->env_list), del_env);
	ft_lstclear(&(mini->doc_list), del_token);
	ft_lstclear(&(mini->main_list), del_command);
	free_darr(mini->env_arr);
	free(mini);
    exit(0);
}
