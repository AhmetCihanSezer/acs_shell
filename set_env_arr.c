#include "minishell.h"

int	len_list(t_list *list)
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

int in_charset(char c, char *set)
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

char	*find_name(t_list *env, char *str)
{
	while (env)
	{
		if (!ft_strncmp(((t_env *)env->content)->name, str, ft_strlen(str) + 1))
			return (ft_strdup(((t_env *)env->content)->key));
		env = env->next;
	}
	return (ft_strdup(""));
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

