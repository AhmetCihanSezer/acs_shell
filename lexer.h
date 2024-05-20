#ifndef LEXER_H
#define LEXER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/readline.h>
#include "enviroment.h"

typedef struct s_token
{
    char *value;
    int term;
} t_token;

#define LESS 1
#define GREAT 2
#define DLESS 3
#define DGREAT 4
#define INFILE 5
#define OUTFILE 6
#define PIPE 7
#define CMD 8
#define ARG 9


#endif