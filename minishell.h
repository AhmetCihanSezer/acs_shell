#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "./libft/libft.h"

typedef struct s_minishell
{
	t_list	*token_list;
	t_list	*env_list;
	t_list  *doc_list;
	t_list  *main_list;
	char	**env_arr;
	int		in_file;
	int		out_file;
	int		num_pipe;
	int		pipe[2];
	int		status;
}	t_minishell;

char	*take_pwd(void);
void	pwd(void);
void	cd(char **arg, t_minishell *mini);
void	echo(char **arg, int lock1, int lock2);
void	env(t_list *env);
void	del_env(void *content);
void	free_darr(char **arr);
void	built_in_exit(t_minishell *mini);
void	export(char **arg, t_minishell *mini);
void	unset(char **arg, t_minishell *mini);



typedef struct s_env
{
	char	*name;
	char	*key;
}	t_env;


t_list	*ft_sort_env(t_list *env);
t_env	*set_env(char *env);
t_list	*set_env_list(char **envp);




#define OPEN_W_TR O_WRONLY | O_TRUNC | O_CREAT
#define OPEN_W_AP O_WRONLY | O_APPEND | O_CREAT

typedef struct s_command
{
	char    **arg;
	t_list  *infile_list;
	t_list  *outfile_list;
}   t_command;

typedef struct s_token
{
	char	*value;
	int		term;
}	t_token;

char	*tweezers(char *head, char *tail);

#define LESS 1
#define GREAT 2
#define DLESS 3
#define DGREAT 4
#define INFILE 5
#define OUTFILE 6
#define PIPE 7
#define CMD 8
#define ARG 9
#define SNG_PARAM 10
#define NRM_PARAM 11

char	*find_cmd_path(char *cmd, char **envp);

int 	in_charset(char c, char *set);
char	*find_name(t_list *env, char *str);
int		len_list(t_list *list);

void	exec_ve(t_minishell *mini, t_command *command) ;
void    execute_l(t_minishell *mini, t_command *command);
char	**env_list_to_arr(t_list *env_list);

#endif