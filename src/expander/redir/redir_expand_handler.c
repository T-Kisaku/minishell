#include "ast.h"
#include "expander.h"

t_error	*redir_expand_handler(t_redir *redir, t_minishell_state *shell)
{
	t_error	*error;

	error = NULL;
	if (redir->type == REDIR_HERE_DOC)
	{
		if (redir->redirect_source.filename_token->type == TOKEN_UNQUOTED_WORD)
		{
			error = expand_single_token(redir->redirect_source.filename_token,
					shell);
			if (is_error(error))
				return (error);
		}
	}
	else if (redir->redirect_source.filename_token->type != TOKEN_SINGLE_QUOTED_WORD)
	{
		error = expand_single_token(redir->redirect_source.filename_token,
				shell);
		if (is_error(error))
			return (error);
	}
	return (NULL);
}
