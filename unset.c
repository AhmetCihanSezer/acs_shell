#include "minishell.h"

void	unset(char **arg, t_minishell *mini, t_list **env_list)
{
	t_list  *env;
	int i;

	if (!arg[1])
		return;
		//exit(0);
	i = 1;
	while (arg[i])
	{
		env = *(env_list);
		if (!ft_strncmp(((t_env *)env->content)->name, arg[i], ft_strlen(arg[i]) + 1))
		{
			write(1, "aa\n", 3);
			*(env_list) = env->next;
			//ft_lstdelone(env, del_env);
		}
		else
		while (env)
		{
			if (!ft_strncmp(((t_env *)env->content)->name, arg[i], ft_strlen(arg[i]) + 1))
			{
				ft_lstdelone(env, del_env);
				break ;
			}
			env = env->next;
		}
		i++;
	}



	// t_list  *env;
	// int i;

	// if (!arg[1])
	// 	return;
	// 	//exit(0);
	// i = 1;
	// while (arg[i])
	// {
	// 	env = mini->env_list;
	// 	if (!ft_strncmp(((t_env *)env->content)->name, arg[i], ft_strlen(arg[i]) + 1))
	// 	{
	// 		mini->env_list = env->next;
	// 		ft_lstdelone(env, del_env);
	// 	}
	// 	while (env)
	// 	{
	// 		if (!ft_strncmp(((t_env *)env->content)->name, arg[i], ft_strlen(arg[i]) + 1))
	// 		{
	// 			ft_lstdelone(env, del_env);
	// 			break ;
	// 		}
	// 		env = env->next;
	// 	}
	// 	i++;
	// }
	//exit(0);
}

int main(int argc, char const *argv[], char **envp)
{
	t_minishell mini;
	char *arr[] = {"isim=ahmet:cihan", "soyisim=sezer", "okul=ITU", NULL};
	mini.env_list = set_env_list(arr);
	t_list *head;
	head = mini.env_list;
	while (head)
	{
		printf("%s=%s\n", ((t_env *)head->content)->name,((t_env *)head->content)->key);
		head = head->next;
	}
	printf("---------------------\n");
	unset((char **)argv, &mini, &(mini.env_list));
	head = mini.env_list;
	while (head)
	{
		printf("%s=%s\n", ((t_env *)head->content)->name,((t_env *)head->content)->key);
		head = head->next;
	}
	return 0;
}

