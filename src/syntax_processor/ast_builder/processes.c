
#include "libft.h"
#include "token.h"
#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "syntax_processor/ast_builder.h"

static int process_and_or(t_list **token_list_ptr, t_list **cmd_list);
static int process_pipe(t_list **token_list_ptr, t_list **andor_list_ptr);
static int process_word(t_list **token, t_list **andor_list_ptr);
static int process_redirs(t_list **token, t_list **andor_list_ptr);

int handle_token_for_ast(t_list **token_list_ptr, t_list **ast_ptr) {
  t_token *token;
  if (!token_list_ptr || !*token_list_ptr || !ast_ptr || !*ast_ptr)
    return (EXIT_FAILURE);
  token = lstget_token(*token_list_ptr);
  if (is_word_token(token->type))
    return (process_word(token_list_ptr, ast_ptr));
  else if (token->type == TOKEN_PIPE)
    return (process_pipe(token_list_ptr, ast_ptr));
  else if (is_redir_token(token->type))
    return (process_redirs(token_list_ptr, ast_ptr));
  else if (is_control_op_token(token->type))
    return process_and_or(token_list_ptr, ast_ptr);
  return (EXIT_FAILURE);
}

static int process_and_or(t_list **token_list_ptr,
                          t_list **andor_list_ptr) { // TODO: error handling
  t_and_or *last_and_or;
  t_token *current_token;
  last_and_or = get_last_and_or(andor_list_ptr);
  current_token = lstget_token(*token_list_ptr);
  if (current_token->type == TOKEN_AND_IF)
    last_and_or->op_next = OP_AND;
  else if (current_token->type == TOKEN_OR_IF)
    last_and_or->op_next = OP_OR;
  else // TODO: error
    return (EXIT_INTERNAL_ERR);
  lstadd_back_and_or(andor_list_ptr, OP_NONE);
  return (EXIT_OK);
}

static int process_pipe(t_list **token_list_ptr, t_list **andor_list_ptr) {
  t_and_or *last_andor = get_last_and_or(andor_list_ptr);
  if (!token_list_ptr || !*token_list_ptr || !last_andor ||
      !last_andor->pipeline->command_list)
    return (EXIT_INTERNAL_ERR);
  if (advance_token(token_list_ptr) != 0)
    return (EXIT_INTERNAL_ERR);
  if (lstadd_back_command(&last_andor->pipeline->command_list, CMD_SIMPLE) ==
      NULL)
    return (EXIT_INTERNAL_ERR);
  return (EXIT_OK);
}

static int process_word(t_list **token_list_ptr, t_list **andor_list_ptr) {
  t_command *last_cmd;
  last_cmd = get_last_cmd(andor_list_ptr);

  if (!token_list_ptr || !*token_list_ptr || !last_cmd) {
    dev_error();
    return (EXIT_INTERNAL_ERR);
  }
  if (lstcopy_back_token(&last_cmd->u.simple.token_list,
                         *lstget_token(*token_list_ptr)) == NULL)
    return (EXIT_INTERNAL_ERR);
  last_cmd->u.simple.argc++;
  return (advance_token(token_list_ptr));
}

static int process_redirs(t_list **token_list_ptr, t_list **andor_list_ptr) {
  t_redir_type type;
  t_command *last_cmd;
  last_cmd = get_last_cmd(andor_list_ptr);

  if (!token_list_ptr || !*token_list_ptr || !last_cmd)
    return (EXIT_INTERNAL_ERR);
  // TODO: handle error properly
  if (!*token_list_ptr)
    return (EXIT_INTERNAL_ERR);
  type = get_redir_type(lstget_token(*token_list_ptr)->type);
  if (advance_token(token_list_ptr) != 0)
    return (EXIT_INTERNAL_ERR);
  if (lstadd_back_redir(&last_cmd->redir_list, type,
                        lstget_token(*token_list_ptr)) == NULL)
    return (EXIT_INTERNAL_ERR);


  return (advance_token(token_list_ptr));
}
