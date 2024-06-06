#include "minishell.h"

int main(int argc, char const *argv[], char ** evnp)
{
    t_minishell mini;

    mini.env_list = set_env_list(evnp);
    printf("%s\n",find_name(mini.env_list, "HOME"));
    return 0;
}
