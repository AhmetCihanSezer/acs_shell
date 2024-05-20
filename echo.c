#include "builtin.h"

int ft_echo(const char *text, const char *arg)
{
    printf("%s", text);
    if (strcmp(arg, "-n") != 0)
        printf("\n");
}
