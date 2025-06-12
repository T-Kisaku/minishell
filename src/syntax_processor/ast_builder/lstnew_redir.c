#include "ast.h"
#include "libft.h"
#include "token.h"
#include "utils.h"
#include <stdlib.h> // malloc,

t_list		*lstnew_redir_two(t_redir_type type, t_list *token);
static void	init_redir(t_redir *redir, t_redir_type type);

static void	set_redir(t_redir *redir, t_token_content *content);

t_list	*lstnew_redir_two(t_redir_type type, t_list *token)
{
	t_redir			*redir;
	t_list			*next_token;
	t_token_content	*content;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	init_redir(redir, type);
	next_token = token->next;
	content = (t_token_content *)token->content;
	del_token_content(content);
	free(token);
	if (!next_token)
		return (NULL);
	token = next_token;
	content = (t_token_content *)token->content;
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
	t_redir_target *target;

	if (redir->type == REDIR_INPUT || redir->type == REDIR_HERE_DOC)
	{
		target = &redir->to;
		target->fd = 0;
	}
	else if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
	{
		target = &redir->from;
		target->fd = 1;
	}
	target->filename_token = content;
}
