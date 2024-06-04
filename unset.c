#include "minishell.h"

static void	del_env_node(char *arg, t_list **head)
{
    t_list *temp = *head;
    t_list *prev;

	if (!arg)
		return ;
    if (temp != NULL && !ft_strncmp(((t_env *)temp->content)->name,
		arg, ft_strlen(arg) + 1))
    {
        *head = temp->next;
        ft_lstdelone(temp, del_env);
        return ;
    }
    while (temp != NULL && ft_strncmp(((t_env *)temp->content)->name,
		arg, ft_strlen(arg) + 1))
    {
        prev = temp;
        temp = temp ->next;
    }
    if (!temp)
        return ;
    prev->next = temp->next;
    ft_lstdelone(temp, del_env);
}

void	unset(char **arg, t_minishell *mini)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		del_env_node(arg[i], &(mini->env_list));
		i++;
	}
	exit(0);
}
