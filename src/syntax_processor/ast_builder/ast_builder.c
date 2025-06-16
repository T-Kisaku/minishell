#include "ast.h"
#include "syntax_processor/ast_builder.h"
#include "utils/utils.h"
#include <stdbool.h> //bool,

t_ast *ast_builder(t_list **tokens);
static void *free_all_return_null(t_list **tokens, t_ast **ast);

// subshell, &&, ||については未実装
t_ast *ast_builder(t_list **tokens) {
  t_ast *ast;
  t_and_or *and_or;

	if (!tokens || !*tokens)
		return (NULL);
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (free_all_return_null(tokens, &ast));
	ast->next = NULL;
	and_or = malloc(sizeof(t_and_or));
	if (!and_or)
		return (free_all_return_null(tokens, &ast));
	ast->content = and_or;
	and_or->op_next = OP_NONE;
	and_or->pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!and_or->pipeline)
		return (free_all_return_null(tokens, &ast));
	if (build_ast_from_tokens(tokens, ast) != 0)
		return (free_all_return_null(tokens, &ast));
	return (ast);
}

static void *free_all_return_null(t_list **tokens, t_ast **ast) {
  free_token_list(tokens);
  free_ast(ast);
  return (NULL);
}
