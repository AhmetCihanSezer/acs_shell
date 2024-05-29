#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char head[256];
  char operator[256];
  char param[256];
} Token;

int count_quite(const char *string, char ch) {
  int count = 0;
  while (*string) {
    if (*string == ch)
      count++;
    string++;
  }
  return count;
}

int control_quite(const char *string) {
  char see_quite = '\0';
  int inner_quite = 0;
  int i = 0;
  while (string[i] != '\0') {
    if ((string[i] == '"' || string[i] == '\'') && see_quite == '\0' &&
        inner_quite == 0) {
      see_quite = string[i];
      inner_quite = 1;
    } else if (inner_quite == 1 && string[i] == see_quite) {
      inner_quite = 0;
      see_quite = '\0';
    }
    i++;
  }
  return (inner_quite == 0 && see_quite == '\0');
}

Token *define_token(const char *str_) {
  static Token token;
  memset(&token, 0, sizeof(Token));
  char operators[][3] = {"<<", ">>", "<", ">", "&", "\"", "'", "-"};
  char head[256] = {0};
  int i = 0;
  int operator_found = 0;

  // Trim leading and trailing whitespaces
  const char *start = str_;
  while (*start == ' ')
    start++;
  const char *end = start + strlen(start) - 1;
  while (end > start && *end == ' ')
    end--;
  int length = end - start + 1;

  char *trimmed_str = (char *)malloc(length + 1);
  strncpy(trimmed_str, start, length);
  trimmed_str[length] = '\0';

  if (trimmed_str[0] == '<') {
    strcpy(token.operator, "<");
    strcpy(token.head, strrchr(trimmed_str, ' ') + 1);
    strncpy(token.param, trimmed_str + 1,
            strlen(trimmed_str) - strlen(token.head) - 1);
    if (strchr(token.param, '<')) {
      strcpy(token.param, strchr(token.param, '<') + 1);
    }
    free(trimmed_str);
    return &token;
  }

  while (i < strlen(trimmed_str)) {
    for (int j = 0; j < sizeof(operators) / sizeof(operators[0]); j++) {
      if (strncmp(trimmed_str + i, operators[j], strlen(operators[j])) == 0) {
        operator_found = 1;
        strcpy(token.operator, operators[j]);
        break;
      }
    }
    if (operator_found) {
      strncpy(token.head, trimmed_str, i);
      token.head[i] = '\0';
      i += strlen(token.operator);
      break;
    }
    i++;
  }

  if (strcmp(token.operator, "'") == 0 || strcmp(token.operator, "\"") == 0) {
    token.operator[0] = '\0';
    i--;
  }

  strcpy(token.param, trimmed_str + i);

  if (!control_quite(token.param)) {
    printf("Kesme işareti kapatılmadı\n");
    free(trimmed_str);
    return NULL;
  }

  free(trimmed_str);
  return &token;
}

void split_tokens(const char *str_) {
  char *commands = strdup(str_);
  char *command = strtok(commands, "|");
  while (command != NULL) {
    Token *token = define_token(command);
    if (token != NULL) {
      printf("|head: %s |operator: %s |param: %s\n", token->head,
             token->operator, token->param);
    }
    command = strtok(NULL, "|");
  }
  free(commands);
}

int main() {
  const char *prompts[] = {" cat        <   'dosya.txt' 'yeni\".txt' ",
                           " cat        <   'dosya.txt' 'yeni\".txt'\" ",
                           " cat        <   'dosya.txt'         ",
                           " cat<'dosya.txt' ",
                           " cat<'\"dosya.txt' ",
                           " cat<\"dosya'.txt\" ",
                           " cat<'dosya.txt'\" ",
                           " cat<'<dosya.txt' ",
                           " cat'<dosya.txt' ",
                           "<dosya.txt cat",
                           "< dosya.txt < dosya2.txt cat"};

  int num_prompts = sizeof(prompts) / sizeof(prompts[0]);

  for (int i = 0; i < num_prompts; i++) {
    split_tokens(prompts[i]);
  }

  return 0;
}
