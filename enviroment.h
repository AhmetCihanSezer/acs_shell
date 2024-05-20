#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "builtin.h"



typedef struct s_list
{
	void			*content;
	struct s_list	*next;
} t_list;

typedef struct s_data
{
    char *title;
    char *var;
} t_data;


char	**ft_split(char const *s, char c);
t_list *ft_sort_env(t_list *env);
t_list *ft_set_env(char **env);
t_list *ft_cpylst(t_list *lst);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);


#endif