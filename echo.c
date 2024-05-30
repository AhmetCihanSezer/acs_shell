#include "builtin.h"

static int  is_allsame(char *str, char c)
{
    int i;

    i = 0;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (str[i] != c)
            return (0);
        i++;
    }
    return (1);
}

int echo(char **arg)
{
    int i;
    int lock;

    lock = 0;
    i = 0;
    while (arg[i] && arg[i + 1])
    {
        if (arg[i][0] == '-' && is_allsame(&arg[i][1], 'n'))
            lock = 1;
        else
            printf("%s ", arg[i]);
        i++;
    }
    if (arg[i])
        if (arg[i][0] == '-' && is_allsame(&arg[i][1], 'n'))
            lock = 1;
        else
            printf("%s", arg[i]);
    if (!lock)
        printf("\n");
    return 1;
}
