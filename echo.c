#include "minishell.h"

static int	is_allsame(char *str, char c)
{
	int i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **arg, int lock1, int lock2)
{
	int i;

	i = 1;
	while (arg[i] && arg[i + 1])
	{
		if (arg[i][0] == '-' && is_allsame(&arg[i][1], 'n') && !lock2)
			lock1 = 1;
		else
		{
			printf("%s ", arg[i]);
			lock2 = 1;
		}
		i++;
	}
	if (arg[i])
		if (arg[i][0] == '-' && is_allsame(&arg[i][1], 'n') && !lock2)
			lock1 = 1;
		else
			printf("%s", arg[i]);
	if (!lock1)
		printf("\n");
	exit(0);
}
