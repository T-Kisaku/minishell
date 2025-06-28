#include "expander.h"

static t_error *process_simple(t_list *head);

t_error *quote_removal_handler(t_command *cmd , t_list *env_list) {
	(void)env_list;
  t_error *error;
  error = NULL;
  if (cmd->type == CMD_SIMPLE) {
    error = process_simple(cmd->u.simple.token_list);
    if (is_error(error))
      return error;
  }
  return error;
}

static t_error *process_simple(t_list *head) {
  t_list *cur;
  t_token *cur_token_content;
  t_error *error;
  error = NULL;

  cur = head;
  while (cur) {
    cur_token_content = (t_token *)cur->content;
    error = quote_remove_core(cur_token_content);
    if (is_error(error))
      return error;
    cur = cur->next;
  }
  return NULL;
}
