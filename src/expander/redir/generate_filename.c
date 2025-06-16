#include "ast.h"

int			generate_filename_handler(t_redir *target);

int	generate_filename_handler(t_redir *target)
{
	if(target->type == REDIR_HERE_DOC)
		return (EXIT_SUCCESS);
	if (target->to.is_direct_to_fd)
		return (EXIT_SUCCESS);
	target->to.filename = ft_strdup(target->to.filename_token->value);
	if (!target->to.filename)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}



