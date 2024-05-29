#include "enviroment.h"
#include <stdio.h>
#include <unistd.h>

typedef struct s_token {
    char *command;
    char *param;
    char operator;
} t_token;

typedef struct s_token_list {
    t_token *content;
    struct s_token_list *next;
    struct s_token_list *prev;
} t_token_list;

int startswith(char *str1, char *str2) {
  int i;

  i = 0;
  while (str1[i] && str2[i] && str1[i] == str2[i])
    i++;
  if (i == ft_strlen(str2))
    return (1);
  return (0);
}
int endswith(char *str1, char *str2) {
  int i;
  int length;
  int length2;

  length = ft_strlen(str1) - 1;
  length2 = ft_strlen(str2) - 1;
  i = 0;
  while (str1[length - i] && str2[i] && str1[length - i] == str2[length2 - i])
    i++;
  if (i == ft_strlen(str2))
    return (1);
  return (0);
}
char *append_string(char *str1, char *str2) {
  int i;
  int j;
  char *str3;

  i = 0;
  j = 0;
  str3 = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
  while (str1[i]) {
    str3[i] = str1[i];
    i++;
  }
  while (str2[j]) {
    str3[i + j] = str2[j];
    j++;
  }
  str3[i + j] = '\0';
  return (str3);
}
char *strip(char *str) {
  int i;
  int j;

  i = 0;
  j = ft_strlen(str) - 1;
  while (str[i] && (str[i] == ' ' || str[i] == '\t')) {
    i++;
  }
  while (j >= 0 && (str[j] == ' ' || str[j] == '\t')) {
    j--;
  }
  return (ft_substr(str, i, j + 1));
}
char *lstrip(char *str) {
  int i;
  int j;

  i = 0;
  j = ft_strlen(str) - 1;
  while (str[i] && (str[i] == ' ' || str[i] == '\t')) {
    i++;
  }
  return (ft_substr(str, i, j + 1));
}
char *rstrip(char *str) {
  int j;

  j = ft_strlen(str) - 1;
  while (j >= 0 && (str[j] == ' ' || str[j] == '\t')) {
    j--;
  }
  return (ft_substr(str, 0, j + 1));
}
int indexOf(char *str, char *str2, int start) {
  int i;
  int j;
  int length;

  length = ft_strlen(str2);
  i = start;
  while (str[i]) {
    j = 0;
    while (str[i + j] == str2[j] && str2[j]) {
      j++;
    }
    if (j == length)
      return (i);
    i++;
  }
  return (-1);
}
char *replace(char *str, char *old, char *new_s) {
  char *new_str;
  int i;
  int last;

  new_str = ft_strdup("");
  last = 0;
  while (indexOf(str, old, last) != -1) {
    i = 0;
    while (str[i]) {
      if (startswith(str + i, old) == 1) {
        new_str = append_string(new_str, ft_substr(str, last, i));
        new_str = append_string(new_str, new_s);
        i += ft_strlen(old);
        last = i;
      }
      i++;
    }
  }
  new_str = append_string(new_str, ft_substr(str, last, ft_strlen(str)));
  return (new_str);
}
char get_operator(char *command) {
  if (indexOf(command, "<", 0) != -1)
    return ('<');
  if (indexOf(command, ">", 0) != -1)
    return ('>');
  if (indexOf(command, "$", 0) != -1)
    return ('$');
  if (indexOf(command, "<<", 0) != -1)
    return ('!');
  if (indexOf(command, ">>", 0) != -1)
    return ('?');
  return ('\0');
}
void split_command_and_param(char *str, t_token *command) {
  char **str_split;

  str = strip(str);
  if (indexOf(str, "<", 0) != -1)
    str_split = ft_split(str, '<');
  if (indexOf(str, ">", 0) != -1)
    str_split = ft_split(str, '>');
  if (indexOf(str, "$", 0) != -1)
    str_split = ft_split(str, '$');
  if (indexOf(str, "<<", 0) != -1)
    str_split = ft_split(replace(str, "<<", "<"), '<');
  if (indexOf(str, ">>", 0) != -1)
    str_split = ft_split(replace(str, ">>", ">"), '>');
  command->command = str_split[0];
  command->param = str_split[1];
}

t_token_list *parse(char *prompt) {
  char **commands;
  t_token_list *node;
  int i;
  t_token *comnd;
  t_token_list *next_node;

  node = (t_token_list *)malloc(sizeof(t_token_list));
  node->prev = NULL;
  commands = ft_split(prompt, '|');
  while (*commands != NULL) { // commands NULL olana kadar döngü devam eder
    comnd = (t_token *)malloc(sizeof(t_token));
    char operator= get_operator(*commands);
    split_command_and_param(*commands, comnd);

    next_node = (t_token_list *)malloc(sizeof(t_token_list));
    // Bellekten yer ayır
    if (next_node == NULL)
      break;
    comnd->operator= operator;

    next_node->content = comnd;
    next_node->next = NULL; // Sonraki düğümü NULL olarak ayarla
    next_node->prev = node;

    node->next = next_node;
    node = next_node;
    commands++; // Pointer'ı bir sonraki elemana ilerlet
  }
  return (node);
}
t_token_list *get_list_start(t_token_list *list) {
  while (list->prev) {
    list = list->prev;
  }
  return list->next;
}
int main(void) {
  char deneme[46] = "cat $dosya.txt | cat >> deneme.txt | dene < a";
  t_token_list *parses = parse(deneme);
  parses = get_list_start(parses);
  while (parses) {
      printf("token-> command: %s param: %s operator: %c\n",
        parses->content->command ? parses->content->command : "NULL",
        parses->content->param ? parses->content->param : "NULL",
            parses->content->operator ? parses->content->operator : 'n'
            );

      parses = parses->next;
  }

  return (0);
}