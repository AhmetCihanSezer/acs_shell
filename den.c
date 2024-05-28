#include "execute.h"

int main()
{
    int fd[2];
    pipe(fd);

    int pid = fork();
    char **com = {"/usr/bin/cat", NULL};
    if (pid == 0)
    {
        if (execve("/usr/bin/cat", com,NULL) == -1)
            perror("execve: ");
    }   

}

