#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/readline.h>
#include "./libft/libft.h"

void    pwd(void);
//int cd(char **arg, t_minishell *minishell);
int echo(char **arg);
int env(t_list *env);
//void built_in_exit(t_minishell *minishell);
//void ft_unset(char **arg, t_minishell *minishell);



typedef struct s_data
{
    char *name;
    char *value;
} t_data;


t_list *ft_sort_env(t_list *env);
t_list *set_env(char **env);




#define OPEN_W_TR O_WRONLY | O_TRUNC | O_CREAT
#define OPEN_W_AP O_WRONLY | O_APPEND | O_CREAT
typedef struct s_minishell
{
    t_list *env;
    t_list *infile_list;
    t_list *outfile_list;
    t_list *param_list;
    t_list  *doc_list;
    t_list  *current_doc;
    char *cmd;
    char **env_arr;
    char **param_arr;
    int in_file;
    int out_file;
    int num_infile;
    int num_outfile;
    int num_pipe;
    int pipe[2];
    int status;
    
} t_minishell;




typedef struct s_token
{
    char *value;
    int term;
} t_token;

char *tweezers(char *head, char *tail);

#define LESS 1
#define GREAT 2
#define DLESS 3
#define DGREAT 4
#define INFILE 5
#define OUTFILE 6
#define PIPE 7
#define CMD 8
#define ARG 9


char *find_cmd_path(char *cmd, char **envp);

#endif