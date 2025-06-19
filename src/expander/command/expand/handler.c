#include "ast.h"
#include "token.h"
#include "expander/expander.h"

int	expand_handler(t_command *cmd);
static int	expand_token_list(t_list **tokens);

int	expand_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (expand_token_list(&cmd->u.simple.token_list) != 0)
			return (1);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		if (process_expansion(cmd->u.subshell.and_or_list) != 0)
			return (1);
	}
	return (0);
}

static int	expand_token_list(t_list **tokens)
{
	t_list *cur_token;
	t_token_content *cur_token_content;

	cur_token = *tokens;
	while (cur_token)
	{
		cur_token_content = (t_token_content *)cur_token->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD
			|| cur_token_content->type == TOKEN_DOUBLE_QUOTED_WORD)
		{
			if (expand_single_token(cur_token->content) != 0)
				return (1);
		}
		cur_token = cur_token->next;
	}
	return (0);
}
