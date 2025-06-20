#include "expander.h"

int quote_removal_handler(t_command *cmd);
static int process_simple(t_list *head);
static int count_quotes(char *s);
static int copy_without_quotes(char *dst, const char *src);

int quote_removal_handler(t_command *cmd) {
  if (cmd->type == CMD_SIMPLE) {
    if (process_simple(cmd->u.simple.token_list) != 0)
      return (1);
  }
  return (0);
}

static int process_simple(t_list *head) {
  t_list *cur;
  t_token *cur_token_content;
  size_t value_len;
  int quote_count;
  char *tmp;

  cur = head;
  while (cur) {
    cur_token_content = (t_token *)cur->content;
    value_len = ft_strlen(cur_token_content->value);
    quote_count = count_quotes(cur_token_content->value);
    tmp = malloc(sizeof(char) * (value_len - quote_count + 1));
    if (!tmp)
      return (1);
    if (copy_without_quotes(tmp, cur_token_content->value) != 0)
      return (1);
    free(cur_token_content->value);
    cur_token_content->value = tmp;
    cur = cur->next;
  }
  return (0);
}

static int count_quotes(char *s) {
  int quote_count;

  if (!s)
    return (-1);
  quote_count = 0;
  while (*s) {
    if (*s == '\'' || *s == '"')
      quote_count++;
    s++;
  }
  return (quote_count);
}

static int copy_without_quotes(char *dst, const char *src) {

  if (!dst || !src)
    return (1);
  while (*src) {
    if (*src != '\'' && *src != '"') {
      *dst = *src;
      dst++;
    }
    src++;
  }
  *dst = '\0';
  return (0);
}
