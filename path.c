#include "execute.h"

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

char	*find_value(char **envp, char *name)
{   int	i;

	i = 0;
	while(envp[i])
	{
		if (!strncmp(name, envp[i], ft_strlen(name)))
		{
			return (&envp[i][5]);
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



int main(int argc, char const *argv[], char **envp)
{
	if (find_cmd_path("eco", envp))
		printf("%s\n", find_cmd_path("echo", envp));

	// int i = 0;
	// while (cmd_arr[i])
	// {
	// 	printf("%s\n", cmd_arr[i]);
	// 	i++;
	// }
	return 0;
}

