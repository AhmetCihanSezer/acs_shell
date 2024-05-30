#include "minishell.h"

// infile and outfile list

void	exec_ve(t_minishell *minishell)
{
	char	*cmd;
	char	*path;

	cmd = minishell->cmd;
	if (cmd == '/' ||  cmd == '.')
		execve(cmd, minishell->param_arr, minishell->env_arr);
	else
	{
		path = find_cmd_path(cmd, minishell->env_arr);
		if (!path)
			return ;
		free(minishell->param_arr[0]);
		minishell->param_arr[0] = path;
		execve(path, minishell->param_arr, minishell->env_arr);
	}
    perror("CMD: ");
}

int set_infile(t_minishell *minishell)
{
    t_list *head;
    int fd;

    head = minishell->infile_list;
    while (head)
    {
        fd = open(head->content, O_RDONLY); // düzelt
        if (fd == -1)
        {
            perror("INFILE: ");
            return (NULL);
        }
        dup2(fd, minishell->in_file);
        if (!head->next)
            close(fd);
        head = head->next;
    }
}

int set_outfile(t_minishell *minishell)
{
    t_list *head;
    int fd;

    head = minishell->outfile_list;
    while (head)
    {
        if (head->content == DGREAT)
            fd = open(head->content, OPEN_W_AP, 0664); // düzelt
        else
            fd = open(head->content, OPEN_W_TR, 0664); 
        if (fd == -1)
        {
            perror("OUTFILE: ");
            return (NULL);
        }
        dup2(fd, minishell->out_file);
        if (!head->next)
            close(fd);
        head = head->next;
    }
}

int head_executiion(t_minishell *minishell)
{
    int i;
    int fd;
    t_list *token;
    char *cmd;

    if (!set_infile(minishell))
        return (NULL);
    dup2(minishell->pipe[1], minishell->out_file);
    if (!set_outfile(minishell))
        return (NULL);
    execute(minishell);
    return (NULL);
}

int mid_executiion(t_minishell *minishell)
{
    int i;
    int fd;
    t_list *token;
    char *cmd;

    dup2(minishell->pipe[0], minishell->in_file);
    if (!set_infile(minishell))
        return (NULL);
    dup2(minishell->pipe[1], minishell->out_file);
    if (!set_outfile(minishell))
        return (NULL);
    execute(minishell);
    return (NULL);
}



void    execute(t_minishell *minishell)
{
    char    *cmd;

    cmd = minishell->cmd;
    if (ft_strncmp(cmd, "cd", 3))
        cd(&(minishell->param_arr[1]), minishell);
    else if (ft_strncmp(cmd, "pwd", 4))
        pwd();
    else if (ft_strncmp(cmd, "echo", 5))
        echo(&(minishell->param_arr[1]));
    else if (ft_strncmp(cmd, "env", 4))
        env(minishell->env);
    else if (ft_strncmp(cmd, "exit", 5))
        built_in_exit(minishell);
    else if (ft_strncmp(cmd, "unset", 6))
        unset(&(minishell->param_arr[1]), minishell);
    else if (ft_strncmp(cmd, "export", 7))
        export(); //bitmedi bu
    else
        exec_ve(minishell);
}

int mid_executiion(t_minishell *minishell)
{
    int i;
    int fd;
    t_list *token;
    char *cmd;

    dup2(minishell->pipe[0], minishell->in_file);
    if (!set_infile(minishell))
        return (NULL);
    if (!set_outfile(minishell))
        return (NULL);
    execute(minishell);
    return (NULL);
}

int execute(t_minishell *minishell)
{
    int i;
    int pid;
    int status;

    if (!pipe(minishell->pipe))
    {
        perror("pipe: ");
        return (NULL);
    }
    i = minishell->num_pipe;
    while (i > -1)
    {
        pid = fork();
        if (pid == 0)
        {
            if (minishell->num_pipe == i)
                if (!head_execution())
                    return (NULL);
            else if (i == 0)
                if (!tail_execution())
                    return (NULL);  
            else
                if (!mid_execution())
                    return (NULL);
        }
        else
        {
            wait(&status);
            minishell->status = status;
        }
        i--;
    }
    close(minishell->pipe[0]);
    close(minishell->pipe[1]);
    return (1);
}
