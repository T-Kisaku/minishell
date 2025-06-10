#ifndef AST_BUILDER_H
# define AST_BUILDER_H


# include <stdlib.h> //for getenv,
#include "../../../libft/libft.h"
# include "../../ast.h"
// # include "../../utils/utils.h"


t_command *parse_simple_command(t_token_list **cur) ;

//test
int main(void);
#endif