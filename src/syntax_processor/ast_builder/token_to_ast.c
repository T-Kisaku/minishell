#include "ast.h"
#include "exit_status.h"
#include "syntax_processor/ast_builder.h"
#include "utils/utils.h"
#include <stdbool.h> //bool,

static void free_all(t_list **tokens, t_ast **ast);

// subshell, &&, ||については未実装
int token_to_ast(t_list **tokens, t_ast **ast_ptr) {
  t_and_or *and_or;

  if (!tokens || !*tokens)
    return (EXIT_INTERNAL_ERR);
  *ast_ptr = malloc(sizeof(t_ast));
  if (!*ast_ptr) {
    free_all(tokens, ast_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  (*ast_ptr)->next = NULL;
  and_or = malloc(sizeof(t_and_or));
  if (!and_or) {
    free_all(tokens, ast_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  (*ast_ptr)->content = and_or;
  and_or->op_next = OP_NONE;
  and_or->pipeline = malloc(sizeof(t_pipeline));
  if (!and_or->pipeline) {
    free_all(tokens, ast_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  if (build_ast_from_tokens(tokens, ast_ptr) != 0) {
    free_all(tokens, ast_ptr);
    return (EXIT_INTERNAL_ERR);
  }
  return (EXIT_OK);
}

static void free_all(t_list **tokens, t_ast **ast) {
  free_token_list(tokens);
  free_ast(ast);
}
