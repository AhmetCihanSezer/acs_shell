#include "execute.h"

// infile and outfile list

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
    if (execve(minishell->cmd, minishell->param_arr, minishell->env_arr) == -1)
        perror("CMD: ");
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
    if (execve(minishell->cmd, minishell->param_arr, minishell->env_arr) == -1)
        perror("CMD: ");
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
    if (!set_outfile(minishell))
        return (NULL);
    if (execve(minishell->cmd, minishell->param_arr, minishell->env_arr) == -1)
    //          /bin/ls        "/bin/ls", "-a", "adrghetr", evnp
        perror("CMD: ");
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
