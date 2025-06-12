#include "ast.h"
#include "ast_builder.h"
#include "utils/utils.h"

void	process_word(t_list *token, t_command *cmd);
int	process_pipe(t_list *token, t_list *cmd_list);
int	process_redirs(t_list *token, t_command *cmd);

void	process_word(t_list *token, t_command *cmd)
{
	t_list	*next;

	ft_lstadd_back(&cmd->u.simple.token_list, token);
	next = token->next;
	token->next = NULL;
}

int	process_pipe(t_list *token, t_list *cmd_list)
{
	t_list	*new_cmd_list;
	t_list	*next_token;

	new_cmd_list = malloc(sizeof(t_list));
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
	t_list			*new_redir;
	t_redir_type	type;

	content = (t_token_content *)token->content;
	if (content->type == TOKEN_REDIR_INPUT)
		type = REDIR_INPUT;
	else if (content->type == TOKEN_REDIR_OUTPUT)
		type = REDIR_OUTPUT;
	else if (content->type == TOKEN_REDIR_HERE_DOC)
		type = REDIR_HERE_DOC;
	else if (content->type == TOKEN_REDIR_APPEND)
		type = REDIR_APPEND;
	new_redir = lstnew_redir_two(type, token);
	if (!new_redir)
		return (1);
	ft_lstadd_back(&cmd->redir_list, new_redir);
	return (0);
}
