#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	return (0);
}

t_list	*ft_sort_env(t_list *env)
{
	t_env	*swap;
	t_list	*tmp;

	tmp = env;
	while(env->next != NULL)
	{
		if (ft_strcmp(((t_env *)env->content)->name,
			((t_env *)(env->next->content))->name) > 0)
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

t_list	*ft_cpylst(t_list *lst)
{
	t_list	*head;

	head = NULL;
	while (lst)
	{
		ft_lstadd_back(&head, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (head);
}

static void	show_ordered(t_list *env)
{
	t_list	*temp;

	temp = ft_cpylst(env);
	temp = ft_sort_env(temp);
	while (temp)
	{
		if (!ft_strncmp(((t_env *)temp->content)->name, "_", 2))
		{
			temp = temp->next;
			continue ;
		}
		printf("declare -x %s", ((t_env *)temp->content)->name);
		if (((t_env *)temp->content)->key)
			printf("=\"%s\"", ((t_env *)temp->content)->key);
		printf("\n");
		temp = temp->next;
	}
}

static int	cheat(t_list *env, t_env *temp)
{
	if (!ft_strncmp(((t_env *)env->content)->name, temp->name, ft_strlen(temp->name) + 1))	
	{
		if (!temp->key)
		{
			del_env(temp);
			return (1);
		}
		del_env(env->content);
		env->content = (void *) temp;
		return (1) ;
	}
	return (0);
}

void	export(char **arg, t_minishell *mini)
{
	int		i;
	t_list	*env;
	t_env	*temp;

	if (!arg[1])
		show_ordered(mini->env_list);
	i = 1;
	while (arg[i])
	{	
		temp = set_env(arg[i]);
		env = mini->env_list;
		while (env)
		{
			if (cheat(env, temp))
				break ;
			env = env->next;
		}
		if (!env)
			ft_lstadd_back(&(mini->env_list), ft_lstnew((void *)temp));
		i++;
	}
	exit (0);
}

// int main(int argc, char const *argv[], char **env)
// {
// 	t_minishell mini;
// 	// t_list *kamil;
// 	// t_list *temp;
// 	// char *envp[] = {"isim=ahmet:cihan", "soyisim=sezer", "okul=itu", NULL};
// 	// int i = 0;
// 	// while (envp[i])
// 	// {
// 	// 	printf("%s\n", envp[i]);
// 	// 	i++;
// 	// }
// 	mini.env_list = set_env_list(env);
// 	// t_list *head= mini.env_list;
// 	// ft_lstadd_back(&head, ft_lstnew((void *) set_env("baba=yilmaz")));
// 	// //t_env *razi = set_env("baba=yilmaz");
// 	// //printf("%s/\\%s\n", razi->name, razi->key);

// 	// // temp = (kamil = ft_cpylst(mini.env_list));
// 	// // temp = ft_sort_env(temp);
// 	// while (head)
// 	// {
// 	// 	printf("%s/\\%s\n", ((t_env *)head->content)->name, ((t_env *)head->content)->key);
// 	// 	head = head->next;
// 	// }







// 	//show_ordered(mini.env_list);
// 	// while (temp)
// 	// {
// 	// 	printf("%s/\\%s\n", ((t_env *)temp->content)->name, ((t_env *)temp->content)->key);
// 	// 	temp = temp->next;
// 	// }
// 	// temp = kamil;
// 	// temp = ft_cpylst(mini.env_list);
// 	// temp = ft_sort_env(temp);
// 	// while (temp)
// 	// {
// 	// 	printf("%s/\\%s\n", ((t_env *)temp->content)->name, ((t_env *)temp->content)->key);
// 	// 	temp = temp->next;
// 	// }
// 	while (1)
// 	{
// 		export(ft_split(readline("> "), ' '), &mini);
// 	}
// 	//export((char **)argv, &mini); 
// 	return 0;
// }
