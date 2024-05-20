#include "enviroment.h"

int	n_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '=' && *s2 != '=')
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s1);
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;
	t_list	*last;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		temp = *lst;
		last = ft_lstlast(temp);
		last->next = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

char **ft_split_equ(char *env)
{
	int i;
	int j;
	char **splited;
	char *temp;

	splited = (char **)malloc(2 * sizeof(char *));
	i = 0;
	while(env[i] != '=' && env[i])
		i++;
	temp = (char *) malloc(sizeof(char) * i);
	i = 0;
	while (env[i] != '=' && env[i])
	{
		temp[i] = env[i];
		i++;
	}
	temp[i] = '\0';
	splited[0] = temp;
	splited[1] = NULL;
	if (env[i])
	{
		j = 0;
		while (env[j + i + 1])
			j++;
		temp = (char *) malloc(sizeof(char) * j);
		j = 0;
		while (env[j + i + 1])
		{
			temp[j] = env[i + 1 + j];
			j++;
		}
		temp[j] = '\0';
		splited[1] = temp;
	}
	return (splited);
}

t_list *ft_set_env(char **env)
{
    t_list *new_env;
    t_list *temp;
	t_data *data;
	char **splited;
    int i;

    if (!env)
        return (NULL);
    new_env = (t_list *) malloc(sizeof(t_list));
	data = (t_data *) malloc(sizeof(t_data));
	splited = ft_split_equ(env[0]);
	data->title = splited[0];
	data->var = splited[1];
    new_env->content = (void *) data;
    new_env->next = NULL;
    i = 1;
    while (env[i])
    {
        temp = (t_list *)malloc(sizeof(t_list));
		data = (t_data *) malloc(sizeof(t_data));
		splited = ft_split_equ(env[i]);
		data->title = splited[0];
		data->var = splited[1];
        temp->content = (void *) data;
        temp->next = NULL;
        ft_lstadd_back(&new_env, temp);
        i++;
    }
    return (new_env);
}

t_list *ft_sort_env(t_list *env)
{
	t_data *swap;
	t_list	*tmp;

	tmp = env;
	while(env->next != NULL)
	{

		if (strcmp(((t_data *)env->content)->title, ((t_data *)(env->next->content))->title) > 0)
		{
			swap = env->content;
			env->content = env->next->content;
			env->next->content = swap;
			env = tmp;
		}
		else
			env = env->next;
	}
	env = tmp;
	return (env);
}

t_list *ft_cpylst(t_list *lst)
{
	t_list *head;

	head = NULL;
	while (lst)
	{
		ft_lstadd_back(&head, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (head);
}

// int main(int argc, char const *argv[], char **env)
// {
// 	char ** asd = ft_split_equ("asd=dfr");
// 	printf("%s -=- %s", asd[0], asd[1]);
//     t_list *head = ft_set_env(env);
// 	while (head)
// 	{
// 		printf("%s -=- %s\n", ((t_data *) head->content)->title, ((t_data *)head->content)->var);
// 		head = head->next;
// 	}
// 	t_list *cpy = ft_cpylst(head);
// 	t_list *sorted = ft_sort_env(head);
//     while (sorted)
//     {
// 		printf("%s -=- %s\n", ((t_data *) sorted->content)->title, ((t_data *)sorted->content)->var);
//         sorted = sorted->next;
//     }
// 	printf("----------------\n");
// 	while (cpy)
//     {
//         printf("%s\n", (char *) cpy->content);
//         cpy = cpy->next;
//     }
//     return 0;
// }
