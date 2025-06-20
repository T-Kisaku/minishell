#include "ast.h"
#include "expander.h"

int	redir_expand_handler(t_redir *redir);

int	redir_expand_handler(t_redir *redir)
{
	if (redir->type == REDIR_HERE_DOC)
	{
		if (redir->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD)
		{
			if (expand_single_token(redir->redirect_source.filename_token) != 0)
				return (1);
		}
	}
	else if (redir->redirect_source.filename_token->type != TOKEN_SINGLE_QUOTED_WORD)
	{
		if (expand_single_token(redir->redirect_source.filename_token) != 0)
			return (1);
	}
	return (0);
}
