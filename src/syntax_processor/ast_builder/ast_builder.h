#ifndef AST_BUILDER_H
# define AST_BUILDER_H

# include "ast.h"
# include "token.h"
# include <stdbool.h>

//ast_builder.c
t_ast	*ast_builder(t_list **tokens);
//create_cmd_list.c
int		create_command_list(t_list **cmd_list);
//build_ast_from_token.c
int		build_ast_from_tokens(t_list **tokens, t_ast *ast);
int		advance_token(t_list **token, t_list *next_token, bool is_free);
//processes.c
int					process_word(t_list **token, t_list **cmd_list);
int					process_pipe(t_list **token, t_list **cmd_list);
int					process_redirs(t_list **token, t_list **cmd_list);
//create_redir_list.c
t_list	*create_redir_list(t_redir_type type, t_list *filename_token);

//test
int		main(void);
#endif