#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "enviroment.h"
#include "./libft/libft.h"
#include "execute.h"
#include "lexer.h"


char *pwd(void);
//int cd(char **arg, t_minishell *minishell);
int echo(char **arg);
int env(t_list *env);
//void built_in_exit(t_minishell *minishell);


#endif