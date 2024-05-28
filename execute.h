#ifndef EXECUTE_H
#define EXECUTE_H

#include "enviroment.h"
#include "builtin.h"


typedef struct s_minishell
{
    t_list *env;
    int num_infile;
    int num_outfile;
    int num_pipe;
    int pipe[2];
    
} t_minishell;


#endif