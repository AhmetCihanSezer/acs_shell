#include "minishell.h"

static int	len_list(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

static char	*join_name_key(t_env *env)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin(env->name, "=");
	str = ft_strjoin(temp, env->key);
	free(temp);
	return (str);
}

static int in_charset(char c, char *set)
{
    int i = 0;
    while (set[i])
    {
        if (c == set[i])
            return 1;
        i++;
    }
    return (0);
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

static char	*find_name(t_list *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(((t_env *)env->content)->name, str, ft_strlen(str) + 1))
			return (ft_strdup(((t_env *)env->content)->key));
		env = env->next;
	}
	return (ft_strdup(""));
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

t_token *temp(char *s1, int s2)
{
	t_token *result;

	result = malloc(sizeof(t_token));
	result->term = s2;
	result->value = ft_strdup(s1);
	return (result);
}

int main(int argc, char const *argv[], char **env)
{
	t_minishell mini;
	t_list *arg_list;

	mini.status = 32;
	mini.env_arr = env;
	mini.env_list = set_env_list(env);
	arg_list = NULL;
	ft_lstadd_back(&arg_list, ft_lstnew(temp("Ahmet $$HOME $Sezer", NRM_PARAM)));
	ft_lstadd_back(&arg_list, ft_lstnew(temp("Muhendisim $ben", SNG_PARAM)));
	ft_lstadd_back(&arg_list, ft_lstnew(temp("naber $asd $?bebek", NRM_PARAM)));
	ft_lstadd_back(&arg_list, ft_lstnew(temp("ben kelebek", SNG_PARAM)));
	char **arg = arg_list_to_arr(arg_list, &mini);
	int i = 0;
	char *a =malloc(1);
	a = malloc(22);
	while (arg[i])
	{
		printf("%s\n", arg[i]);
		i++;
	}
	system("leaks a.out");
	return 0;
}


char	**env_list_to_arr(t_list *env_list)
{
	char	**arr;
	int		i;
	t_env	*env;

	arr = (char **) malloc(sizeof(char *) * (len_list(env_list) + 1));
	i = 0;
	while (env_list)
	{
		env = env_list->content;
		if (!env->key)
		{
		env_list = env_list->next;
			continue ;
		}
		arr[i] = join_name_key(env);
		env_list = env_list->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

