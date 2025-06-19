#include "token.h"
#include <stdbool.h>

bool	is_word_token(e_token_type type);
bool	is_redir_token(e_token_type type);
bool	is_control_op_token(e_token_type type);

bool	is_word_token(e_token_type type)
{
	if (type == TOKEN_UNQUOTED_WORD || type == TOKEN_SINGLE_QUOTED_WORD
		|| type == TOKEN_DOUBLE_QUOTED_WORD)
		return (true);
	else
		return (false);
}

bool	is_redir_token(e_token_type type)
{
	if (type == TOKEN_REDIR_INPUT ||
		type == TOKEN_REDIR_OUTPUT ||
		type == TOKEN_REDIR_HERE_DOC ||
		type == TOKEN_REDIR_APPEND)
		return (true);
	else
		return (false);
}

bool	is_control_op_token(e_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_AND_IF || type == TOKEN_OR_IF)
		return (true);
	else
		return (false);
}
