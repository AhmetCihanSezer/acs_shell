#include "builtin.h"
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd = open("text.txt", O_RDONLY);
    
    char *name = ttyname(fd);
    printf("%s\n", name);
    return 0;
}
