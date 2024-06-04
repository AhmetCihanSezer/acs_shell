#include "minishell.h"

static char	*find_dolar(char * str)
{
	char	*dolar;
	int		i;

	dolar = ft_strchr(str, '$');
	if (!dolar)
		return (ft_strdup(""));
	i = dolar - str;
	while (str[i] && !in_charset(str[i], " \t\n"))
		i++;
	dolar = tweezers(dolar, &str[i]);
	return (dolar);
}
