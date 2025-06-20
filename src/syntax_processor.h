#ifndef SYNTAX_PROCESSOR_H
#define SYNTAX_PROCESSOR_H

#include "libft.h"
#include "ast.h"
#include "error.h"

t_error *str_to_token(char *input_str, t_list **token_list_ptr);
t_error *token_to_ast(t_list *token_list, t_ast **ast_ptr);

#endif
