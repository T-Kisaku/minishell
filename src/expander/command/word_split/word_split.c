#include "expander.h"
#include "utils/ms_string.h"

t_error *word_split_handler(t_command *cmd);
static t_error *process_simple(t_list *head);
static int count_words(char *str);

t_error *word_split_handler(t_command *cmd) {
  t_error *error;
  error = NULL;

  if (cmd->type == CMD_SIMPLE) {
    error = process_simple(cmd->u.simple.token_list);
    if (is_error(error))
      return error;
    cmd->u.simple.argc = ft_lstsize((t_list *)cmd->u.simple.token_list);
  }
  return NULL;
}

t_error *process_simple(t_list *head) {
  t_list *cur;
  t_token *cur_token_content;
  int word_count;
  t_error *error;
  error = NULL;

  cur = head;
  while (cur) {
    cur_token_content = cur->content;
    if (cur_token_content->type == TOKEN_UNQUOTED_WORD) {
      word_count = count_words(cur_token_content->value);
      if (word_count > 1) {
        error = split_token(cur, word_count);
        if (is_error(error))
          return error;
      }
    }
    cur = cur->next;
  }
  return error;
}
static int count_words(char *str) {
  int word_count;

  if (!str)
    return (-1);
  word_count = 0;
  while (*str) {
    while (ms_isspace(*str))
      str++;
    if (*str && !ms_isspace(*str)) {
      word_count++;
      while (*str && !ms_isspace(*str))
        str++;
    }
  }
  return (word_count);
}
