#ifndef SYNTAX_PROCESSOR_H
#define SYNTAX_PROCESSOR_H

#include "libft.h"
#include "ast.h"

t_list *tokenizer(char *string);
t_ast *ast_builder(t_list *tokens);
int process_expansion(t_ast *ast);

#endif
