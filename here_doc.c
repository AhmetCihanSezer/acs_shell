#include "minishell.h"

void	here_doc(char *doc, t_minishell *mini)
{
	int	fd;
	char	*str;
	t_list	*head;

	fd = open(doc, O_CREAT | O_WRONLY, 0777);
	str = readline("> ");
	while (ft_strncmp(str , doc, ft_strlen(doc)))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("> ");
	}
	close(fd);
	head = mini->doc_list;
	ft_lstadd_back(&(mini->doc_list), ft_lstnew((void *)doc));	
}

int main(int argc, char const *argv[])
{
	t_minishell *mini;

	mini = malloc(sizeof(t_minishell));
	int i = 0;
	char **arg = (char **) &argv[1];
	while (arg[i])
	{
		here_doc(arg[i], mini);
		i++;
	}
	t_list *doc = mini->doc_list;
	while (doc)
	{
		printf("%s\n", (char *)doc->content);
		doc = doc->next;
	}
	return 0;
}