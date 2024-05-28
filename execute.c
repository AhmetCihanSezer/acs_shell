#include "execute.h"




int head_executiion()
{

}


int execute(t_minishell minishell)
{
    int i;

    if (!pipe(minishell.pipe))
    {
        perror("pipe: ");
        return (NULL);
    }
    if (minishell.num_pipe >= 0)
        if (!head_execution())
            return (NULL);
    i = minishell.num_pipe;
    while (i > 1)
    {
        if (!mid_execution())
            return (NULL);
        i--;
    }
    if (minishell.num_pipe >= 1)
        if (!tail_execution())
            return (NULL);
    close(minishell.pipe[0]);
    close(minishell.pipe[1]);
    return (1);
}