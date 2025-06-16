#include "expander/expander.h"

int			generate_argv_handler(t_command *cmd);
static int	process_simple(t_command *cmd);

int	generate_argv_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (process_simple(cmd) != 0)
			return (1);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		//not impliment
	}
	if (cmd->u.simple.argv == NULL)
		return (1);
	else
		return (0);
}

static int	process_simple(t_command *cmd)
{
	t_list			*cur_token;
	t_token_content	*cur_token_content;
	int			index;

	cmd->u.simple.argv = malloc(sizeof(char *) * (cmd->u.simple.argc + 1));
	if (!cmd->u.simple.argv)
		return (1);
	cur_token = cmd->u.simple.token_list;
	index = 0;
	while (index < cmd->u.simple.argc)
	{
		cur_token_content = cur_token->content;
		cmd->u.simple.argv[index] = ft_strdup(cur_token_content->value);
		if (!cmd->u.simple.argv[index])
		{
			free_argv(&cmd->u.simple.argv, index);
			return (1);
		}
		index++;
		cur_token = cur_token->next;
	}
	cmd->u.simple.argv[index] = NULL;
	return (0);
}
