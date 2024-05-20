#include "builtin.h"

char *ft_pwd(void)
{
    char *buf;

    buf = (char *) malloc(260);
    if (!getcwd(buf, 260))
    {
        free(buf);
        perror("cd: ");
        return (NULL);
    }
    return (buf);
}
