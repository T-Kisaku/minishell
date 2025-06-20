#include "ast.h"
#include "expander.h"

int	redir_expand_handler(t_redir *redir);

int	redir_expand_handler(t_redir *redir)
{
	if (redir->type == REDIR_HERE_DOC)
	{
		if (redir->to.filename_token->type == TOKEN_UNQUOTED_WORD)
		{
			if (expand_single_token(redir->to.filename_token) != 0)
				return (1);
		}
	}
	else if (redir->to.filename_token->type != TOKEN_SINGLE_QUOTED_WORD)
	{
		if (expand_single_token(redir->to.filename_token) != 0)
			return (1);
	}
	return (0);
}
