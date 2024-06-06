#include "minishell.h"


//  gcc deneme.c execute.c path.c exit.c cd.c pwd.c echo.c env.c unset.c export.c enviroment.c set_env_arr.c ./libft/libft.a -lreadline

int main(int argc, char const *argv[], char **envp)
{
    char *str;
    char **arg;
    int status;
    t_command cmd;
    t_minishell mini;

    mini.env_arr = envp;
    mini.env_list = set_env_list(envp);

    while (1)
    {
        str = readline("> ");
        add_history(str);
        cmd.arg = ft_split(str, ' ');
        //cmd.arg[0] = find_cmd_path(cmd.arg[0], mini.env_arr);
            mini.env_arr = env_list_to_arr(mini.env_list);
            execute_l(&mini, &cmd);
            //perror("Execve: ");
    }

    return 0;
}

