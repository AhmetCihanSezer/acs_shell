#include "minishell.h"

void	exec_ve(t_minishell *mini, t_command *command) 
{
	char	*path;

	if (command->arg[0][0] == '/' ||  command->arg[0][0] == '.')
		execve(command->arg[0], command->arg, mini->env_arr);
	else
	{
		path = find_cmd_path(command->arg[0], mini->env_arr);
		if (!path)
			return ;
		free(command->arg[0]);
		command->arg[0] = path;
		execve(command->arg[0], command->arg, mini->env_arr);
	}
	perror("CMD: ");
}



//  set status
void    execute_l(t_minishell *mini, t_command *command)
{
	int	pid;
	int status;

	if (!ft_strncmp(command->arg[0], "cd", 3))
		cd(command->arg, mini);
	else if (!ft_strncmp(command->arg[0], "exit", 5))
		built_in_exit(mini);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!ft_strncmp(command->arg[0], "pwd", 4))
			pwd();
			else if (!ft_strncmp(command->arg[0], "echo", 5))
			echo(command->arg, 0, 0);
			else if (!ft_strncmp(command->arg[0], "env", 4))
			env(mini->env_list);
			else if (!ft_strncmp(command->arg[0], "unset", 6))
			unset(command->arg, mini);
			else if (!ft_strncmp(command->arg[0], "export", 7))
			export(command->arg, mini); 
			else
			exec_ve(mini, command);
		}
		wait(&status);
	}
}

// exit yerine return yap

void	set_infile(t_minishell *mini, t_command *command)
{
	t_list *head;
	int fd;

	head = command->infile_list;
	while (head)
	{
		fd = open(((t_token *)head->content)->value, O_RDONLY); // düzelt
		if (fd == -1)
		{
			perror("INFILE: ");
			exit(1);
		}
		if  (!head->next)
		{
			dup2(fd, 0);
			return ;
		}
		close(fd);
		head = head->next;
	}
}

// exit yerine return yap

void	set_outfile(t_minishell *mini, t_command *command)
{
	t_list *head;
	int fd;

	head = command->outfile_list;
	while (head)
	{
		if (((t_token *)head->content)->term == DGREAT)
			fd = open(head->content, OPEN_W_AP, 0664); // düzelt
		else
			fd = open(head->content, OPEN_W_TR, 0664); 
		if (fd == -1)
		{
			perror("OUTFILE: ");
			exit(1);
		}
		if  (!head->next)
		{
			dup2(fd, 1);
			return ;
		}
		close(fd);
		head = head->next;
	}
}

void	head_execution(t_minishell *mini, t_command *command)
{
	set_infile(mini, command);
	if (mini->num_pipe != 0)
		dup2(mini->pipe[1], mini->out_file);
	set_outfile(mini, command);
	execute_l(mini, command);
}

void	mid_execution(t_minishell *mini, t_command *command)
{
	dup2(mini->pipe[0], mini->in_file);
	set_infile(mini, command);
	dup2(mini->pipe[1], mini->out_file);
	set_outfile(mini, command);
	execute_l(mini, command);
}

void	tail_execution(t_minishell *mini, t_command *command)
{
	dup2(mini->pipe[0], mini->in_file);
	set_infile(mini, command);
	set_outfile(mini, command);
	execute_l(mini, command);
}

void	execute(t_minishell *mini)
{
	t_list	*head;
	int		i;

	head = mini->main_list;
	i = mini->num_pipe;
	while (i > -1)
	{
		if (mini->num_pipe == i)
			head_execution(mini, ((t_command *)head->content));
		else if (i == 0)
			tail_execution(mini, ((t_command *)head->content));
		else
			mid_execution(mini, ((t_command *)head->content));
		head = head->next;
		i--;
	}
}

// void	execute(t_minishell *mini)
// {
// 	t_list	*head;
// 	int		pid;
// 	int		i;
// 	int		status;

// 	head = mini->main_list;
// 	i = mini->num_pipe;
// 	while (i > -1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (mini->num_pipe == i)
// 				head_execution(mini, ((t_command *)head->content));
// 			else if (i == 0)
// 				tail_execution(mini, ((t_command *)head->content));
// 			else
// 				mid_execution(mini, ((t_command *)head->content));
// 		}
// 		wait(&status);
// 		mini->status = WEXITSTATUS(status);
// 		head = head->next;
// 		i--;
// 	}
// }

// int execute(t_minishell *minishell)
// {
//     int i;
//     int pid;
//     int status;

//     if (!pipe(minishell->pipe))
//     {
//         perror("pipe: ");
//         return (NULL);
//     }
//     i = minishell->num_pipe;
//     while (i > -1)
//     {
//         pid = fork();
//         if (pid == 0)
//         {
//             if (minishell->num_pipe == i)
//                 if (!head_execution())
//                     return (NULL);
//             else if (i == 0)
//                 if (!tail_execution())
//                     return (NULL);  
//             else
//                 if (!mid_execution())
//                     return (NULL);
//         }
//         else
//         {
//             wait(&status);
//             minishell->status = status;
//         }
//         i--;
//     }
//     close(minishell->pipe[0]);
//     close(minishell->pipe[1]);
//     return (1);
// }
