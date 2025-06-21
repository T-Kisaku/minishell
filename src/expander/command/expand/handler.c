#include "ast.h"
#include "error.h"
#include "token.h"
#include "minishell.h"
#include "expander.h"

static t_error *expand_token_list(t_list **tokens);

t_error *expand_handler(t_command *cmd) {

  t_error *error;
  error = NULL;
  if (cmd->type == CMD_SIMPLE) {
    error = expand_token_list(&cmd->u.simple.token_list);
    if (is_error(error))
      return error;
  } else if (cmd->type == CMD_SUBSHELL) {
    error = process_expansion(cmd->u.subshell.and_or_list);
    if (is_error(error))
      return error;
  }
  return error;
}

static t_error *expand_token_list(t_list **tokens) {
  t_list *cur_token;
  t_token *cur_token_content;
  t_error *error;
  error = NULL;

  cur_token = *tokens;
  while (cur_token) {
    cur_token_content = (t_token *)cur_token->content;
    if (cur_token_content->type == TOKEN_UNQUOTED_WORD ||
        cur_token_content->type == TOKEN_DOUBLE_QUOTED_WORD) {
      error = expand_single_token(cur_token->content);
      if (is_error(error))
        return error;
    }
    cur_token = cur_token->next;
  }
  return error;
}
