#include "minishell.h"

static void	check_arg_num(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 2)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
		exit (1);
	}
}

static void set_pwd(t_list *head)
{
	while (head)
	{
		if (!ft_strncmp("PWD", ((t_env *)head->content)->name, 4))
			{
				free(((t_env *)head->content)->key);
				((t_env *)head->content)->key = take_pwd();
				break ;
			}
		head = head->next;
	}
}

void cd(char **arg, t_minishell *mini)
{
	char	*home;
	check_arg_num(arg);
	if (!arg[1])
	{
		home = find_name(mini->env_list, "HOME");
		chdir(home);
		perror("cd: ");
		free(home);
	}
	else 
	{
		if ((chdir(arg[1])))
		{
		//write(1, arg[0], ft_strlen(arg[0]));
			perror("cd: ");
			return ;
			exit(1);
		}
	}
	set_pwd(mini->env_list);
	return ;
	exit(0);
}


// int main(int argc, char const *argv[], char **envp)
// {
// 	// printf("%c", readline("> "));
// 	char *str;

// 	t_minishell minishell;
// 	t_list *head;
// 	minishell.env = set_env(envp);

// 	head = minishell.env;
// 	while (head)
// 	{
// 		if (!ft_strncmp("PWD", ((t_data *)head->content)->name, 3))
// 			{
// 				break ;
// 			}
// 		head = head->next;
// 	}

// 	while (1)
// 	{
// 		str = readline("> ");
// 		cd(&str, &minishell);
// 		printf("%s=%s\n", ((t_data *)head->content)->name, ((t_data *)head->content)->value);

// 	}

// 	return 0;
// }
