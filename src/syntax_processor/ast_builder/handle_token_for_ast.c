#include "ast.h"
#include "token.h"
#include <stdbool.h> //for bool,

int	handle_token_for_ast(t_list *token,
							t_list *command_list);
static bool	is_word_token(e_token_type type);
static bool	is_redir_token(e_token_type type);

int	handle_token_for_ast(t_list *token, t_list *command_list)
{
	t_command		*cmd;
	t_token_content	*token_content;

	cmd = (t_command *)command_list->content;
	token_content = (t_token_content *)token->content;
	if (is_word_token(token_content->type))
	{
		process_word(token, cmd);
		token = token->next;
		return (0);
	}
	else if (token_content->type == TOKEN_PIPE)
		return (process_pipe(token, command_list));
	else if (is_redir_token(token_content->type))
		return (process_redirs(token, cmd));
	else if (token_content->type == TOKEN_EOF)
		return (2);
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
