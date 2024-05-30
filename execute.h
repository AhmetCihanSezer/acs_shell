#ifndef EXECUTE_H
#define EXECUTE_H

#include "enviroment.h"
#include "builtin.h"
#include "lexer.h"
#include "libft/libft.h"

#define OPEN_W_TR O_WRONLY | O_TRUNC | O_CREAT
#define OPEN_W_AP O_WRONLY | O_APPEND | O_CREAT


typedef struct s_minishell
{
    t_list *env;
    t_list *infile_list;
    t_list *outfile_list;
    t_list *param_list;
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


#endif