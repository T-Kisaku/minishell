#include "expander/expander.h"

int			quote_removal_handler(t_command *cmd);
static int	process_simple(t_list *head);


int	quote_removal_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (process_simple(cmd->u.simple.token_list) != 0)
			return (1);
	}
	return (0);
}

static int	process_simple(t_list *head)
{
	t_list			*cur;
	t_token_content	*cur_token_content;

	cur = head;
	while (cur)
	{
		cur_token_content = (t_token_content *)cur->content;
		if (quote_remove_core(cur_token_content) != 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}
