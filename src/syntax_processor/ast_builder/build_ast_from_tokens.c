#include <stdlib.h>
#include <stdbool.h> //for bool,
#include "ast.h"
#include "syntax_processor/ast_builder.h"
#include "token.h"
#include "utils/utils.h"

int			build_ast_from_tokens(t_list **tokens, t_ast *ast);
static int	handle_token_for_ast(t_list **token, t_list **cmd_list);
static bool	is_word_token(e_token_type type);
static bool	is_redir_token(e_token_type type);
int		advance_token(t_list **token, t_list *next_token, bool is_free);

int	build_ast_from_tokens(t_list **tokens, t_ast *ast)
{
	t_and_or	*and_or;

	and_or = lstget_and_or(ast);
	if (!and_or->pipeline->command_list)
	{
		if (create_command_list(&and_or->pipeline->command_list) != 0)
			return (EXIT_FAILURE);
	}else{
		// TODO: internal error handling
		return (EXIT_FAILURE);
	}
	while (*tokens)
	{
		if (handle_token_for_ast(tokens, &and_or->pipeline->command_list) != 0)
			return (1);
	}
	return (0);
}
static int	handle_token_for_ast(t_list **token, t_list **cmd_list)
{
	t_token_content	*token_content;
	token_content = (t_token_content *)(*token)->content;
	if (is_word_token(token_content->type))
		return (process_word(token, cmd_list));
	else if (token_content->type == TOKEN_PIPE)
		return (process_pipe(token, cmd_list));
	else if (is_redir_token(token_content->type))
		return (process_redirs(token, cmd_list));
	else if (token_content->type == TOKEN_EOF)
		return (advance_token(token, (*token)->next, true));
	else
		return (1);
	return (0);
}

static bool	is_word_token(e_token_type type)
{
	if (type == TOKEN_UNQUOTED_WORD || type == TOKEN_SINGLE_QUOTED_WORD
		|| type == TOKEN_DOUBLE_QUOTED_WORD)
		return (true);
	else
		return (false);
}

static bool	is_redir_token(e_token_type type)
{
	if (type == TOKEN_REDIR_INPUT ||
		type == TOKEN_REDIR_OUTPUT ||
		type == TOKEN_REDIR_HERE_DOC ||
		type == TOKEN_REDIR_APPEND)
		return (true);
	else
		return (false);
}

int	advance_token(t_list **token, t_list *next_token, bool is_free)
{
	t_token_content	*content;

	if (!token || !*token)
		return (1);
	content = (t_token_content *)(*token)->content;
	if (is_free)
	{
		del_token_content(content);
		free(*token);
	}
	*token = next_token;
	return (0);
}
