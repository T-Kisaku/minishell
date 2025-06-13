
#include "ast.h"
#include "ast_builder.h"
#include "utils/utils.h"
#include <stdbool.h>

int					process_word(t_list **token, t_list **cmd_list);
int					process_pipe(t_list **token, t_list **cmd_list);
int					process_redirs(t_list **token, t_list **cmd_list);
static t_redir_type	get_redir_type(e_token_type token_type);
int					advance_token(t_list **token, t_list *next_token,
						bool is_free);

int	process_word(t_list **token, t_list **cmd_list)
{
	t_list	*next;
	t_list *tail;
	t_command *last_cmd;
	tail = ft_lstlast(*cmd_list);
	if(tail == NULL)
	{
		// TODO: internal server error
		return (EXIT_FAILURE);
	}
	last_cmd = lstget_command(tail);

	if (!token || !*token || !last_cmd)
		return (1);
	next = (*token)->next;
	(*token)->next = NULL;
	ft_lstadd_back(&last_cmd->u.simple.token_list, *token);
	last_cmd->u.simple.argc++;
	return (advance_token(token, next, false));
}

int	process_pipe(t_list **token, t_list **cmd_list)
{
	if (!token || !*token || !cmd_list)
		return (1);
	if (advance_token(token, (*token)->next, true) != 0)
		return (1);
	if (create_command_list(cmd_list) != 0)
		return (1);
	return (0);
}

int	process_redirs(t_list **token, t_list **cmd_list)
{
	t_list			*next;
	t_token_content	*content;
	t_redir_type	type;
	t_list			*new_redir;
	t_list *tail;
	t_command *last_cmd;
	tail = ft_lstlast(*cmd_list);
	if(tail == NULL)
	{
		// TODO: internal server error
		return (EXIT_FAILURE);
	}
	last_cmd = lstget_command(tail);

	if (!token || !*token || !last_cmd)
		return (1);
	next = (*token)->next;
	content = (t_token_content *)(*token)->content;
	type = get_redir_type(content->type);
	if (advance_token(token, next, true) != 0)
		return (1);
	if (!*token)
		return (1);
	next = (*token)->next;
	(*token)->next = NULL;
	new_redir = create_redir_list(type, (*token));
	if (!new_redir)
		return (1);
	ft_lstadd_back(&last_cmd->redir_list, new_redir);
	return (advance_token(token, next, false));
}

static t_redir_type	get_redir_type(e_token_type token_type)
{
	t_redir_type	redir_type;

	if (token_type == TOKEN_REDIR_INPUT)
		redir_type = REDIR_INPUT;
	else if (token_type == TOKEN_REDIR_OUTPUT)
		redir_type = REDIR_OUTPUT;
	else if (token_type == TOKEN_REDIR_HERE_DOC)
		redir_type = REDIR_HERE_DOC;
	else if (token_type == TOKEN_REDIR_APPEND)
		redir_type = REDIR_APPEND;
	else
		return (REDIR_INPUT); //default
	return (redir_type);
}
