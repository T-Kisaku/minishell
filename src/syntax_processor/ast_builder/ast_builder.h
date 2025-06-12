#ifndef AST_BUILDER_H
# define AST_BUILDER_H

# include "ast.h"
# include "libft.h"
# include "token.h"
// # include "utils/utils.h"

//ast_builder.c
t_ast		*ast_builder(t_list *tokens);

//build_ast_from_token.c
int			build_ast_from_tokens(t_list *tokens, t_ast *ast);
//create_cmd_list.c
int			create_command_list(t_list **cmd_list);
t_command	*create_command(void);
static void	set_simple(u_command *u);

//handle_token_for_ast.c
int	handle_token_for_ast(t_list *token,
							t_list *command_list);

//processes.c
void		process_word(t_list *token, t_command *cmd);
int			process_pipe(t_list *token, t_list *cmd_list);
int			process_redirs(t_list *token, t_command *cmd);

//lstnew_redir.c
t_list		*lstnew_redir_two(t_redir_type type, t_list *token);

//test
int			main(void);
#endif