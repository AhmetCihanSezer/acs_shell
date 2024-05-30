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


int strlen_s(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*find_value(char **envp, char *name)
{   int	i;

	i = 0;
	while(envp[i])
	{
		if (!ft_strncmp(name, envp[i], strlen_s(envp[i], '=')))
		{
			return (&envp[i][strlen_s(name, '=')+1]);
		}
		i++;
	}
	return (NULL);
}

char *find_cmd_path(char *cmd, char **envp)
{
	char	**cmd_arr;
	char	*temp1;
	char	*temp2;
	int	i;

	cmd_arr = ft_split(find_value(envp, "PATH"), ':');
	i = 0;
	while (cmd_arr[i])
	{
		temp1 = ft_strjoin("/", cmd);
		temp2 = ft_strjoin(cmd_arr[i], temp1);
		free(temp1);
		if (!access(temp2, X_OK))
		{
			free_darr(cmd_arr);
			return (temp2);
		}
		i++;
	}
	free_darr(cmd_arr);
	write(2, "command not found\n", 19);
	return (NULL);
}

int	check_path(char *str)
{
	if (str[0] == '/' || str [0] == '.')
		return (0);
	return (1);
}

int main(int argc, char const *argv[], char **envp)
{
	char **arg;
	
	arg = (char **)argv;
	if (check_path(arg[1]))
	{
		char *cmd_path = find_cmd_path((char *)arg[1], envp);
		arg[1] = cmd_path;
	}
	execve(arg[1], &arg[1], envp);
	perror("Execve: ");
	return 0;
}


// int main(int argc, char const *argv[], char **env)
// {
//     char **arg;

//     arg = malloc(sizeof(char *) * argc);
//     int i = 1;
//     while (i < argc)
//     {
//         arg[i-1] = strdup(argv[i]);
//         i++;
//     }
//     arg[i-1] = NULL; 
//     i = 0;
//     while (arg[i])
//     {
//         printf("%s\n", arg[i]);
//         i++;
//     }
//     execve(arg[0], arg, env);
//     perror("Execve: ");
//     return 0;
// }

// int main(int argc, char const *argv[], char **envp)
// {
// 	if (find_cmd_path((char *)argv[1], envp))
// 		printf("%s\n", find_cmd_path((char *)argv[1], envp));
 

	// int i = 0;
	// while (cmd_arr[i])
	// {
	// 	printf("%s\n", cmd_arr[i]);
	// 	i++;
	// }
// 	return 0;
// }

