#include "ast.h"
#include "libft.h"
#include "token.h"
#include "utils/utils.h"
#include <stdlib.h> // malloc,

t_list		*create_redir_list(t_redir_type type, t_list *token);
static void	init_redir(t_redir *redir, t_redir_type type);
static void	set_redir(t_redir *redir, t_token_content *content);

t_list	*create_redir_list(t_redir_type type, t_list *filename_token)
{
	t_redir			*redir;
	t_token_content	*content;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	init_redir(redir, type);
	content = (t_token_content *)filename_token->content;
	set_redir(redir, content);
	return (ft_lstnew(redir));
}

static void	init_redir(t_redir *redir, t_redir_type type)
{
	redir->type = type;
	redir->from.fd = -1;
	redir->from.filename = NULL;
	redir->from.filename_token = NULL;
	redir->from.is_direct_to_fd = false;
	redir->to.fd = -1;
	redir->to.filename = NULL;
	redir->to.filename_token = NULL;
	redir->to.is_direct_to_fd = false;
}

static void	set_redir(t_redir *redir, t_token_content *content)
{
	if(redir->type == REDIR_INPUT ||
		redir->type == REDIR_HERE_DOC
	)
		redir->from.fd = (STDIN_FILENO);
	else if (redir->type == REDIR_OUTPUT ||
		redir->type == REDIR_APPEND
	)
		redir->from.fd = (STDOUT_FILENO);
	else
	{
		// TODO: error handling for internal error 
		return;	
	}
	redir->from.is_direct_to_fd = true;

	redir->to.filename_token = content;
}
