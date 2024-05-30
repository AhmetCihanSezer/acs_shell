#include "lexer.h"

char *tweezers(char *head, char *tail)
{
    char *str;
    int i;
    if (!tail)
        return (ft_strdup(head));
    if (!head)
        return (NULL);
    str = (char *) malloc(sizeof(char) * (tail - head + 1));
    i = 0;
    while (head != tail)
    {
        str[i] = *head;
        head++;
        i++;
    }
    str[i] = '\0';
    return str;
}

int in_charset(char c, char *set)
{
    int i = 0;
    while (set[i])
    {
        if (c == set[i])
            return 1;
        i++;
    }
    return (0);
}

t_list *ft_special_split(char *line)
{
    int i = 0;
    int j = 0;
    int k;
    t_list *head;
    t_list *temp;

    head = NULL;
    while (line[i])
    {
        k = 0;
        temp = (t_list *) malloc(sizeof(t_list));
        if (in_charset(line[i], " \n\t"))
            i++;
        else
        {
            j = i;
            if (line[i] == '\'')
            {
                j = ++i;
                while (line[i] && line[i] != '\'')
                    i++;
                k = 1;
            }
            else if (line[i] == '"')
            {
                j = ++i;
                while (line[i] && line[i] != '"')
                    i++;
                k = 1;
            }
            else if (in_charset(line[i], "<>|"))
            {
                if ((in_charset(line[i], "<") && in_charset(line[i+1], "<")) ||
                     (in_charset(line[i], ">") && in_charset(line[i+1], ">")))
                    i++;
                i++;
            }
            else
            {
                while (line[i] && !in_charset(line[i], " \n\t<>|'\""))
                    i++;
            }
            if (!line[i] && k == 1)
                return (NULL);
            ft_lstadd_back(&head, ft_lstnew((void *)ft_z(&line[j], &line[i-1])));
            i += k;
        }
    }
    return (head);
}

t_list *ft_set_splitted(int term, void *value)
{
    t_token *token;

    token = (t_token *) malloc(sizeof(t_token));
    token->term = term;
    token->value = value;
    return (ft_lstnew((void *) token));
}

t_list *ft_lexer(t_list *splitted)
{
    int i;
    t_list *head;

    i = 1;
    head = NULL;
    while (splitted)
    {
        if (!strncmp((char *)splitted->content, "<",1))
        {
            write(1, splitted->content, strlen((char *) splitted->content));
            ft_lstadd_back(&head, ft_set_splitted(LESS, NULL));
            splitted = splitted->next;
            ft_lstadd_back(&head, ft_set_splitted(INFILE, splitted->content));
        }
        else if (!strncmp((char *)splitted->content, ">", 1))
        {
            write(1, splitted->content, strlen((char *) splitted->content));
            ft_lstadd_back(&head, ft_set_splitted(GREAT, NULL));
            splitted = splitted->next;
            ft_lstadd_back(&head, ft_set_splitted(OUTFILE, splitted->content));
        }
        else if (!strncmp((char *)splitted->content, "|", 1))
        {
            write(1, splitted->content, strlen((char *) splitted->content));
            ft_lstadd_back(&head, ft_set_splitted(PIPE, NULL));
            i = 1;
        }
        else
        {
            write(1, splitted->content, strlen((char *) splitted->content));
            if (i  && i--)
                ft_lstadd_back(&head, ft_set_splitted(CMD, splitted->content));
            else
                ft_lstadd_back(&head, ft_set_splitted(ARG, splitted->content));
        }
        if (splitted)
            splitted = splitted->next;
    }
    return (head);
}

int main(int argc, char const *argv[])
{
    char *line = "asd > ak a<a '  a  ' b 'ga\"ay'  >> \"n\"\n\\ a<<g  etf asdf ";
    t_list *lst = ft_special_split(line);
    t_list *splitted = ft_lexer(lst);
    //printf("%d\n", in_charset(' ', " "));
    //char *deneme = ft_cımbız(line, line+6);
   // printf("%s\n", deneme);
    int i = 0;
    // while (lst)
    // {
    //     printf("%s\n", (char *)lst->content);
    //      lst = lst->next;
    // }
    
    while (splitted)
    {
        printf("%s\t->%d\n", ((t_token *)splitted->content)->value, ((t_token *)splitted->content)->term);
        splitted = splitted->next;
    }
    return 0;
}
