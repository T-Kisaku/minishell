#include "expander.h"

int		cmd_loop(t_ast *ast, int (*handler)(t_command *));
void	copy_and_advance(t_expansion_context *ctx, char *src, size_t count);

int	cmd_loop(t_ast *ast, int (*handler)(t_command *))
{
	t_list		*cur_list;
	t_and_or	*cur_and_or;
	t_list		*cmd_node;
	t_command	*cmd;

	if (!ast || !handler)
		return (1);
	cur_list = ast;
	while (cur_list)
	{
		cur_and_or = (t_and_or *)(cur_list->content);
		cmd_node = cur_and_or->pipeline->command_list;
		while (cmd_node)
		{
			cmd = (t_command *)(cmd_node->content);
			if (handler(cmd) != 0)
				return (1);
			cmd_node = cmd_node->next;
		}
		cur_list = cur_list->next;
	}
	return (0);
}

void	copy_and_advance(t_expansion_context *ctx, char *src, size_t count)
{
	int	i;

	ft_memcpy(&ctx->output[ctx->index], src, count);
	i = 0;
	while (i < count)
	{
		ctx->cur_pos++;
		ctx->index++;
		i++;
	}
}
