#include "minishell.h"

int main(int argc, char const *argv[])
{
    while (1)
    {
    char *str = readline("> ");
        add_history(str);
    }
    
    
    unlink("EOF");
    return 0;
}
