#include "ast.h"
#include "utils/utils.h"

int	process_word(t_list *token, t_command *cmd)
{
	t_list	*last_token;

	last_token = ft_lstlast(cmd->u.simple.token_list);
	if (last_token)
		last_token->next = token;
	else
		cmd->u.simple.token_list = token;

}

int	process_pipe(t_list *token, t_list *cmd_list)
{
	t_list	*new_cmd_list;
	t_list	*next_token;

	new_cmd_list = malloc(sizeof(t_command));
	if (!new_cmd_list)
		return (1);
	cmd_list->next = new_cmd_list;
	cmd_list = cmd_list->next;
	next_token = token->next;
	free(token);
	token = next_token;
}

int	process_redirs(t_list *token, t_command *cmd)
{
	t_token_content	*content;
	t_redir			*new_redir;
	t_redir			*cur_redir;
	t_redir_type	type;

	content = (t_token_content *)token->content;
	if (content->type == TOKEN_REDIR_INPUT)
		type == REDIR_INPUT;
	else if (content->type == TOKEN_REDIR_OUTPUT)
		type == REDIR_OUTPUT;
	else if (content->type == TOKEN_REDIR_HERE_DOC)
		type == REDIR_HERE_DOC;
	else if (content->type == TOKEN_REDIR_APPEND)
		type == REDIR_APPEND;
	new_redir = lstnew_redir(type, token);
	if (!new_redir)
		return (1);
	cur_redir = ft_lstlast(cmd->redir_list);
	if (cur_redir)
		new_redir = cur_redir;
	else
		cmd->redir_list = cur_redir;
	return (0);
}

int	process_eof(t_list *token)
{
	free_token_list(&token);
	return (2);
}
