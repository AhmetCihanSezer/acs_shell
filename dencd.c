#include "minishell.h"

int main(int argc, char const *argv[])
{
	int	fd;

	fd = open("a.txt", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	fd = open("b.txt", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	fd = open("c.txt", O_RDONLY);
	dup2(fd, 0);
	close(fd);
	char *arg[] = {"/usr/bin/cat", NULL};
	execve(arg[0], arg, NULL);
	perror("cat: ");
	return 0;
}
