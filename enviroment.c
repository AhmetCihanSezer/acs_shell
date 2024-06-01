#include "minishell.h"

char *tweezers(char *head, char *tail)
{
    char *str;
    int i;
    if (!tail)
        return (ft_strdup(head));
    if (!head)
        return (NULL);
    str = (char *) malloc(sizeof(char) * (tail - head + 1));
    i = 0;
    while (head != tail)
    {
        str[i] = *head;
        head++;
        i++;
    }
    str[i] = '\0';
    return str;
}

t_env	*set_env(char *env)
{
	t_env	*data;
	char	*loc;

	data = (t_env *) malloc(sizeof(t_env));
	if (!data)
		return (NULL);
	loc = ft_strchr(env, '=');
	data->name = ft_strdup(tweezers(env, loc));
	if (loc)
		data->key = ft_strdup(loc + 1);
	else
		data->key = NULL;
	return data;
}

t_list	*set_env_list(char **envp)
{
	t_list	*head;
	int	i;
	int	len;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&head, ft_lstnew((void *) set_env(envp[i])));
		i++;
	}
	return (head);
}

// int main(int argc, char const *argv[], char **env)
// {
// 	t_list *head = set_env(env);
// 	while (head)
// 	{
// 		printf("%s = %s \n", ((t_data *)head->content)->name,((t_data *)head->content)->value);
// 		head = head->next;
// 	}

// 	return 0;
// }

// t_list *ft_sort_env(t_list *env)
// {
// 	t_env *swap;
// 	t_list	*tmp;

// 	tmp = env;
// 	while(env->next != NULL)
// 	{
// 		if (strcmp(((t_env *)env->content)->name, ((t_env *)(env->next->content))->key) > 0)
// 		{
// 			swap = env->content;
// 			env->content = env->next->content;
// 			env->next->content = swap;
// 			env = tmp;
// 		}
// 		else
// 			env = env->next;
// 	}
// 	env = tmp;
// 	return (env);
// }

// t_list *ft_cpylst(t_list *lst)
// {
// 	t_list *head;

// 	head = NULL;
// 	while (lst)
// 	{
// 		ft_lstadd_back(&head, ft_lstnew(lst->content));
// 		lst = lst->next;
// 	}
// 	return (head);
// }
