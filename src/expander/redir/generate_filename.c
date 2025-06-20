#include "ast.h"

int			generate_filename_handler(t_redir *target);

int	generate_filename_handler(t_redir *target)
{
	if(target->type == REDIR_HERE_DOC)
		return (EXIT_SUCCESS);
	if (target->redirect_source.is_direct_to_fd)
		return (EXIT_SUCCESS);
	target->redirect_source.filename = ft_strdup(target->redirect_source.filename_token->value);
	if (!target->redirect_source.filename)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}



