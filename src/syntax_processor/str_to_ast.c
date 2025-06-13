#include "ast.h"
#include "syntax_processor.h"

t_ast *str_to_ast(char *input_str)
{
  t_list *token_list;
  t_ast *ast;
  token_list = tokenizer(input_str);
  if(token_list == NULL)
	// TODO: internal error handling
	return NULL;
  ast = ast_builder(&token_list);
  if(ast == NULL)
	// TODO: internal error handling
	return NULL;
   return ast;
}