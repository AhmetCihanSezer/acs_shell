#include "minishell.h"

char *take_pwd(void)
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

void pwd()
{
    char	*path;

	path = take_pwd;
	printf("%s\n", path);
	free(path);
}