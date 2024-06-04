#include "minishell.h"

char *take_pwd(void)
{
	char *buf;

	buf = (char *) malloc(260);
	getcwd(buf, 260);
	//write(1, buf, ft_strlen(buf));
	return (buf);
}

void pwd()
{
	char	*path;

	path = take_pwd();
	printf("%s\n", path);
	free(path);
	exit(0);
}
