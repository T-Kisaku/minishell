#include "error.h"
#include "expander.h"
#include "utils/utils.h"

static t_error *expand_command(t_ast *ast);
static t_error *expand_redir(t_ast *ast);

t_error *process_expansion(t_ast *ast) {
  t_error *error;
  error = NULL;
  error = expand_command(ast);
  if (is_error(error))
    return error;
  error = expand_redir(ast);
  if (is_error(error))
    return error;

  return error;
}
static t_error *expand_command(t_ast *ast) {
  t_error *error;
  error = NULL;
  error = cmd_loop(ast, expand_handler);
  if (is_error(error))
    return error;
  error = cmd_loop(ast, word_split_handler);
  if (is_error(error))
    return error;
  error = cmd_loop(ast, quote_removal_handler);
  if (is_error(error))
    return error;
  error = cmd_loop(ast, generate_argv_handler);
  return error;
}

static t_error *expand_redir(t_ast *ast) {
  t_error *error;
  error = NULL;
  error = redir_loop(ast, input_heredoc_content_handler);
  if (is_error(error))
    return error;
  error = redir_loop(ast, redir_expand_handler);
  if (is_error(error))
    return error;
  error = redir_loop(ast, redir_split_handler);
  if (is_error(error))
    return error;
  error = redir_loop(ast, redir_quote_removal_handler);
  if (is_error(error))
    return error;
  error = redir_loop(ast, generate_heredoc_file_handler);
  if (is_error(error))
    return error;
  error = redir_loop(ast, generate_filename_handler);
  return error;
}
