#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"



typedef struct s_data
{
    char *name;
    char *value;
} t_data;


t_list *ft_sort_env(t_list *env);
t_list *set_env(char **env);



#endif