#include "../../include/tokenizer.h"

int			process_special_char(t_token_context *tc);
static int	process_less_than(t_token_context *tc);
static int	process_greater_than(t_token_context *tc);

int	process_special_char(t_token_context *tc)
{
	if (create_token(tc) != 0)
		return (1);
	if (*tc->cur_str == '<')
		return (process_less_than(tc));
	else if (*tc->cur_str == '>')
		return (process_greater_than(tc));
	else if (*tc->cur_str == '|')
	{
		tc->cur_str++;
		return (set_token(tc, TOKEN_PIPE));
	}
	return (0);
}

// "<" or "<<"
static int	process_less_than(t_token_context *tc)
{
	tc->cur_str++;
	if (*tc->cur_str != '<')
		return (set_token(tc, TOKEN_REDIR_INPUT));
	else if (*tc->cur_str == '<')
	{
		tc->cur_str++;
		return (set_token(tc, TOKEN_REDIR_HERE_DOC));
	}
	return (0);
}

//">" or ">>"
static int	process_greater_than(t_token_context *tc)
{
	tc->cur_str++;
	if (*tc->cur_str != '>')
		return (set_token(tc, TOKEN_REDIR_OUTPUT));
	else if (*tc->cur_str == '>')
	{
		tc->cur_str++;
		return (set_token(tc, TOKEN_REDIR_APPEND));
	}
	return (0);
}
