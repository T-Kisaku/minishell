#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include "ast.h"
# include "token.h"
# include "utils/utils.h"
# include <stdlib.h> //for getenv,

typedef enum
{
	DOLLAR_SPECIAL,
	DOLLAR_VARIABLE,
	DOLLAR_LITERAL
}					e_dollar_type;

typedef struct s_expansion_context
{
	const char		*input;
	char			*output;
	char			*cur_pos;
	char			*next_pos;
	int				index;
	size_t			required_len;
	int				in_single_quote;
	char			*variable;
	e_dollar_type	cur_dollar_type;
}					t_expansion_context;

typedef struct s_split_token_context
{
	t_list			*cur;
	t_list			*tmp;
	t_list			*next;
	char			*original;
	char			*start_str;
	char			*cur_str;
}					t_split_token_context;

typedef enum
{
	SET_MODE_NORMAL,
	SET_MODE_FIGURE
}					e_mode_set_temp;

typedef enum
{
	MODE_CALCULATE,
	MODE_SET_VALUE,
}					e_expander_mode;
//expander.c
int					process_expansion(t_ast *ast);
int					expand_handler(t_command *cmd);
//expand_single_token.c
int					expand_single_token(t_list **token);
//process_expansion_core_core.c
int	process_expansion_core_core(t_expansion_context *ctx,
								e_expander_mode mode);
//expand_variable.c
int					expand_variable(t_expansion_context *ctx);
int					expand_special(t_expansion_context *ctx);
//word_split.c
int					word_split_handler(t_command *cmd);
//split_token.c
int					split_token(t_list *token, int word_count);
//quote_remove.c
int					quote_removal_handler(t_command *cmd);

//generate_argv.c
int					generate_argv_handler(t_command *cmd);
//utils.h
void				copy_and_advance(t_expansion_context *ctx, char *src,
						int count);

//redir
int	input_heredoc_content_handler(t_redir *redir);
int	redir_split_handler(t_redir *redir);
int	redir_quote_removal_handler(t_redir *target);
int	generate_heredoc_file_handler(t_redir *redir);
int	generate_filename_handler(t_redir *target);


//common
int	quote_remove_core(t_token_content *content);

#endif