#include "builtin.h"

char *pwd(void)
{
    char *buf;

    buf = (char *) malloc(260);
    if (!getcwd(buf, 260))
    {
        free(buf);
        perror("pwd: ");
        return (NULL);
    }
    return (buf);
}
