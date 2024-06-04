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

static char	*replace(char *str, char *old_str, char *new_str)
{
	char	*result;
	char	*temp1;
	char	*temp2;

	if (!*old_str)
		return (str);
	temp1 = tweezers(str, ft_strnstr(str, old_str, ft_strlen(str)));
	temp2 = ft_strjoin(temp1, new_str);
	free(temp1);
	result = ft_strjoin(temp2, ft_strnstr(str, old_str, ft_strlen(str)) + ft_strlen(old_str));
	free(temp2);
	free(old_str);
	free(new_str);
	free(str);
	return (result);
}

static char	*replace_l(char *str, char *old_str, char *new_str)
{
	char	*result;
	char	*temp1;
	char	*temp2;

	if (!*old_str)
		return (str);
	temp1 = tweezers(str, ft_strnstr(str, old_str, ft_strlen(str)));
	temp2 = ft_strjoin(temp1, new_str);
	free(temp1);
	result = ft_strjoin(temp2, ft_strnstr(str, old_str, ft_strlen(str)) + 2);
	free(temp2);
	free(old_str);
	free(new_str);
	free(str);
	return (result);
}

static char	*cheat(char *value, t_minishell *mini)
{
	char	*str;
	char	*dolar;

	str = value;
	dolar = find_dolar(value);
	while (dolar[0])
	{
		if (dolar[1] == '?')
			str = replace_l(str, dolar, ft_itoa(mini->status));
		else
			str = replace(str, dolar, find_name(mini->env_list, &(dolar[1])));
		dolar = find_dolar(str);
	}
	free(dolar);
	return (str);
}

char	**arg_list_to_arr(t_list *arg_list, t_minishell *mini)
{
	char	**arr;
	char	*dolar;
	int		i;
	t_token	*arg;

	arr = (char **) malloc(sizeof(char *) * (len_list(arg_list) + 1));
	i = 0;
	while (arg_list)
	{
		arg = arg_list->content;
		if (arg->term  == SNG_PARAM)
			arr[i] = ft_strdup(arg->value);
		else
			arr[i] = cheat(arg->value, mini);
		arg_list = arg_list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
