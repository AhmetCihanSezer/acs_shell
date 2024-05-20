#include "builtin.h"

int ft_cd(char *path)
{
    if (chdir(path) == -1)
    {
        perror("cd: ");
        return (0);
    }
    return (1);
}