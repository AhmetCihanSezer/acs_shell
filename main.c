#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct	s_token
{
	char	*type;
	char	*value;
}	t_token;
typedef struct	s_token_list
{
	t_token				*content;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}	t_token_list;

typedef struct	s_string_list
{
	char					*content;
	struct s_string_list	*next;
	struct s_string_list	*prev;
}	t_string_list;


int	len(char *string_)
{
	int	i;

	i = 0;
	while (string_[i])
		i++;
	return (i);
}
char	*ft_strdup(char *string_)
{
	char	*new_;
	int		i;

	i = 0;
	new_ = malloc(sizeof(char *) * len(string_) + 1);
	while (string_[i])
	{
		new_[i] = string_[i];
		i++;
	}
	new_[i] = '\0';
	return (new_);
}

t_token_list	*create_token_list()
{
	t_token_list	*new;

	new = (t_token_list *)malloc(sizeof(t_token_list));
	if (new == NULL)
		return (NULL);
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	token_list_len(t_token_list *list_)
{
	int	i;

	i = 0;
	while (list_->next != NULL)
	{
		list_ = list_->next;
		i++;
	}
	while (list_->prev != NULL)
		list_ = list_->prev;
	return (i);
}

t_token_list	*token_list_last(t_token_list *list_)
{
	t_token_list	*last;

	while (list_->next != NULL)
		list_ = list_->next;

	last = list_;
	while (list_->prev != NULL)
		list_ = list_->prev;
	return (last);
}

t_token_list	*token_list_get(t_token_list *list_, int index)
{
	int				i;
	t_token_list	*item;

	i = 0;
	while (list_->next != NULL && i != index)
	{
		list_ = list_->next;
		i++;
	}
	item = list_;
	while (list_->prev != NULL)
		list_ = list_->prev;
	if (i != index)
		return (NULL);
	return (item);
}

t_string_list	*string_list_get(t_string_list *list_, int index)
{
	int	i;

	i = 0;
	while (list_->next != NULL && i != index)
	{
		list_ = list_->next;
		i++;
	}
	if (i != index)
		return (NULL);
	return list_;
}

t_token	*create_token(char *type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return NULL;

	new->type = ft_strdup(type);
	new->value = ft_strdup(value);
	return (new);
}

t_string_list	*create_string_list()
{
	t_string_list	*new;

	new = (t_string_list *)malloc(sizeof(t_string_list));
	if (new == NULL)
		return (NULL);
	new->content = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_token	*copy_Token(t_token *token)
{
	return (create_token(token->type, token->value));
}

void	add_token(t_token_list *list_, char *type, char *value)
{
	t_token_list	*new;
	t_token			*token;

	while (list_->next != NULL)
		list_ = list_->next;
	new = create_token_list();
	token = create_token(type, value);
	new->content = copy_Token(token);
	new->prev = list_;
	list_->next = new;
	if (!list_->content)
		list_ = list_->next;
}

void add_token_w_token(t_token_list *list_, t_token *token)
{
	t_token_list *new;

	while (list_->next != NULL)
		list_ = list_->next;
	new = create_token_list();
	new->content = copy_Token(token);
	new->prev = list_;
	list_->next = new;
	if (!list_->content)
		list_ = list_->next;
}

void add_string(t_string_list *list_, char *string_)
{
	t_string_list	*new;

	while (list_->next != NULL)
		list_ = list_->next;
	new = create_string_list();
	new->content = ft_strdup(string_);
	new->prev = list_;
	list_->next = new;
	free(string_);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char *word_dup(const char *str, int start, int finish)
{
	char *word;
	int i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}
// BURDA KALDIM
char **ft_split(char const *s, char c)
{
	size_t i;
	size_t j;
	int index;
	char **split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while ((int)i <= (int)len((char *)s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || (int)i == (int)len((char *)s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
int startswith(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == len(str2))
		return (1);
	return (0);
}
int str_Compare(char *str1, char *str2)
{
	int i;

	i = 0;
	if (len(str1) != len(str2))
		return 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == len(str2))
		return (1);
	return 0;
}
char *substring(char *str, int start, int end)
{
	char *new_string;
	int i;

	i = 0;
	new_string = (char *)malloc(end - start + 1);
	while (start < end)
		new_string[i++] = str[start++];
	new_string[i] = '\0';
	return new_string;
}
char *strip(char *str)
{
	int i;
	int j;

	i = 0;
	j = len(str) - 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (j >= 0 && (str[j] == ' ' || str[j] == '\t'))
		j--;
	return substring(str, i, j + 1);
}
int startswith_operator(char *string_, int i)
{
	char *copy_string;

	copy_string = string_ + i;
	if (len(copy_string) > 1)
	{
		if (copy_string[0] == '<' && copy_string[1] == '<')
			return 2;
		if (copy_string[0] == '>' && copy_string[1] == '>')
			return 2;
	}
	if (copy_string[0] == '<')
		return 1;
	if (copy_string[0] == '>')
		return 1;
	if (copy_string[0] == '|')
		return 1;
	if (copy_string[0] == '$')
		return 1;
	return 0;
}
char *get_operator_name(char *operator)
{
	if (str_Compare(operator, "<") == 1)
		return ft_strdup("LESS");
	else if (str_Compare(operator, ">") == 1)
		return ft_strdup("GREAT");
	else if (str_Compare(operator, ">>") == 1)
		return ft_strdup("DGREAT");
	else if (str_Compare(operator, "<<") == 1)
		return ft_strdup("DLESS");
	else if (str_Compare(operator, "|") == 1)
		return ft_strdup("PIPE");
	return operator;
}
char *get_command(char *operator, char * value)
{
	if (str_Compare(operator, "LESS") == 1)
		return ft_strdup("INFILE");
	else if (str_Compare(operator, "GREAT") == 1)
		return ft_strdup("OUTFILE");
	else if (str_Compare(operator, "DLESS") == 1)
		return ft_strdup("HERE_DOC");
	else if (str_Compare(operator, "DGREAT") == 1)
		return ft_strdup("HERE_DOC");
	else if (strip(value)[0] == '\'')
		return ft_strdup("SNG_PARAM");
	return ft_strdup("NRM_PARAM");
}
int is_split_have_command(t_token_list *token_node_list, int ind)
{
	ind--;
	while (ind > -1)
	{
		if (token_list_get(token_node_list, ind))
		{
			if (str_Compare(token_list_get(token_node_list, ind)->content->type,
							"CMD") == 1)
				return 1;
			if (str_Compare(token_list_get(token_node_list, ind)->content->type,
							"operator") == 1)
				return 0;
		}
		else
			return 0;
		ind--;
	}
	return 0;
}
char *append_string(char *str1, char *str2)
{
	int i;
	int j;
	char *str3;

	i = 0;
	j = 0;
	str3 = malloc(sizeof(char) * (len(str1) + len(str2) + 1));
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		str3[i + j] = str2[j];
		j++;
	}
	str3[i + j] = '\0';
	return str3;
}
char *append_string_char(char *str1, char str2)
{
	int i;
	char *str3;
	if (!str1[0])
	{
		str3 = malloc(sizeof(char *) * 2);
		str3[0] = str2;
		str3[1] = '\0';
		return str3;
	}
	i = 0;
	str3 = malloc(sizeof(char *) * (len(str1) + 2));
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	str3[i] = str2;
	str3[i + 1] = '\0';
	return str3;
}
t_string_list *get_list_head(t_string_list *list_){
	while (list_->prev)
		list_ = list_->prev;
	if (list_->next)
		return list_->next;
	return list_;
}
t_string_list *tokenizer(char *string)
{
	t_string_list   *tokens;
	int             i;
	int             start_command;
	int             in_denden;
	char            *word;
	
	word = ft_strdup("");
	tokens = create_string_list();
	i = 0;
	in_denden = -1;
	while (string[i])
	{
		start_command = startswith_operator(string, i);
		if (start_command != 0 && in_denden == -1)
		{
			if (len(word) > 0)
			{
				add_string(tokens, word);
				word = ft_strdup("");
			}
			add_string(tokens, substring(string, i, i + start_command));
			i += start_command;
		}
		if ((string[i] == ' ' || string[i] == '\t') && in_denden == -1 && len(strip(word)) > 0)
		{
			add_string(tokens, word);
			word = ft_strdup("");
		}
		if (in_denden == 1)
			word = append_string_char(word, string[i]);
		else if (string[i] != ' ' && string[i] != '\t')
			word = append_string_char(word, string[i]);
		if (string[i] == '"' || string[i] == '\'')
			in_denden *= -1;
		i++;
	}
	if (str_Compare(strip(word), "") == 0)
		add_string(tokens, word);
	return get_list_head(tokens);
}
void set_token_type_inner(t_token_list *token_node_list, char *word, int i)
{

	if (str_Compare(token_list_last(token_node_list)->content->value,
					"operator"))
	{
		add_token(token_node_list,
				  get_command(token_list_last(token_node_list)->content->type,
							  word),
				  word);
		token_node_list = token_node_list->next;
	}
	else
	{
		while (token_node_list->prev)
			token_node_list = token_node_list->prev;
		token_node_list = token_node_list->next;
		if (is_split_have_command(token_node_list, i) == 0)
			add_token(token_node_list, "CMD", word);
		else
			add_token(token_node_list,
					  get_command(token_list_last(token_node_list)->content->type,
								  word),
					  word);
	}
}
void set_token_map(t_token_list *token_node_list,char *word, t_string_list *words)
{
	int i;
 
	i = 0;
	while (word)
	{
		if (startswith_operator(word, 0) != 0)
			add_token(token_node_list, get_operator_name(word), "operator");
		else
		{
			if (token_list_len(token_node_list) > 0)
				set_token_type_inner(token_node_list, word, i);
			else
				add_token(token_node_list, "CMD", word);
		}
		i++;
		if (string_list_get(words, i))
			word = string_list_get(words, i)->content;
		else
			word = NULL;
	}
}
t_token_list *set_token_types(t_string_list *words)
{
	t_token_list *token_node_list;
	token_node_list = create_token_list();
	char *word = words->content;
	set_token_map(token_node_list,word,words);
	while (token_node_list->prev)
		token_node_list = token_node_list->prev;
	return token_node_list->next;
}
void denden_checker(char *prompt)
{
	int in_denden;
	int i;

	in_denden = -1;
	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			in_denden *= -1;
		i++;
	}
	if (in_denden == 1)
	{
		printf("Kapatılmamış kesme işareti var ( ' veya \" )");
		exit(0);
	}
}
void checker(char *prompt)
{
	denden_checker(prompt);
	t_token_list *tokens = set_token_types(tokenizer(prompt));
	char *last_token = ft_strdup("");
	char *last_param = ft_strdup("");
	while (tokens->next)
	{
		if (str_Compare(tokens->content->value, "operator") == 1 && str_Compare(last_token, "operator") == 1 && str_Compare(last_param, "PIPE") == 0)
		{
			printf("Ard arda operator geldi!");
			exit(0);
		}
		last_token = tokens->content->value;
		last_param = tokens->content->type;
		tokens = tokens->next;
	}
	if (str_Compare(tokens->content->value, "operator") == 1)
	{
		printf("En sonda operator olamaz!");
		exit(0);
	}
}

t_token_list *parse_prompt(char *prompt)
{
	t_token_list *token_list;
	char **split_prompt;
	int i = 0;

	token_list = create_token_list();
	split_prompt = ft_split(prompt, '|');
	while (split_prompt[i])
	{
		t_string_list *words = tokenizer(split_prompt[i]);
		t_token_list *token_types = set_token_types(words);
		while (token_types->next)
		{
			add_token_w_token(token_list, token_types->content);
			token_types = token_types->next;
		}
		add_token_w_token(token_list, token_types->content);
		add_token(token_list, "PIPE", "operator");
		i++;
	}
	while (token_list->prev)
		token_list = token_list->prev;
	return token_list->next;
}

int main()
{

	char *prompt = ft_strdup(
		"<in.txt < sample.txt cat param1.txt param2.txt \"param3.txt param4.txt\" 'deneme' >out.txt >>app_out.txt |  grep ahmet  <<EOF | wc");

	checker(prompt);
	t_token_list *tokens = parse_prompt(prompt);
	while (tokens->next)
	{
		printf("\ntype:%s  value:%s", tokens->content->type, tokens->content->value);
		tokens = tokens->next;
	}

	return 0;
}