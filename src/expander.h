/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:54 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 17:49:39 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ast.h"
# include "error.h"
# include "libft.h"
# include "minishell.h"
# include "token.h"
# include <stdlib.h> //for getenv,

typedef enum e_dollar_type
{
	DOLLAR_SPECIAL,
	DOLLAR_VARIABLE,
	DOLLAR_LITERAL
}					t_dollar_type;

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
	t_dollar_type	cur_dollar_type;
	t_token_type	*type;
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

typedef enum e_mode_set_temp
{
	SET_MODE_NORMAL,
	SET_MODE_FIGURE
}					t_mode_set_temp;

typedef enum e_expander_mode
{
	MODE_CALCULATE,
	MODE_SET_VALUE,
}					t_expander_mode;

t_error				*expand_handler(t_command *cmd, t_minishell_state *shell);
// word_split.c
t_error				*word_split_handler(t_command *cmd,
						t_minishell_state *shell);
// split_token.c
t_error				*split_token(t_list *token, int word_count);
// quote_remove.c
t_error				*quote_removal_handler(t_command *cmd,
						t_minishell_state *shell);

// generate_argv.c
t_error				*generate_argv_handler(t_command *cmd,
						t_minishell_state *shell);

// redir
t_error				*input_heredoc_content_handler(t_redir *redir,
						t_minishell_state *shell);
t_error				*redir_expand_handler(t_redir *redir,
						t_minishell_state *shell);
t_error				*redir_split_handler(t_redir *redir,
						t_minishell_state *shell);
t_error				*redir_quote_removal_handler(t_redir *target,
						t_minishell_state *shell);
t_error				*generate_heredoc_file_handler(t_redir *redir,
						t_minishell_state *shell);
t_error				*generate_filename_handler(t_redir *target,
						t_minishell_state *shell);

// common
t_error				*quote_remove_core(t_token *content);
// expand_single_token.c
t_error				*expand_single_token(t_token *content,
						t_minishell_state *shell);
// expand_ast_core_core.c
t_error				*expand_ast_core_core(t_expansion_context *ctx,
						t_minishell_state *shell, t_expander_mode mode);
// expand_variable.c
t_error				*expand_variable(t_expansion_context *ctx,
						t_minishell_state *shell);
t_error				*expand_special(t_expansion_context *ctx,
						t_minishell_state *shell);
// utils.h
void				copy_and_advance(t_expansion_context *ctx, char *src,
						int count);
#endif
