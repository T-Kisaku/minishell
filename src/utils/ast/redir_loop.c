#include "ast.h"

int	redir_loop(t_ast *ast, int (*handler)(t_redir *))
{
	t_list	*cur_list;
	t_list	*cmd_node;
	t_list	*redir_list;

	if (!ast || !handler)
		return (1);
	cur_list = ast;
	while (cur_list)
	{
		cmd_node = ((t_and_or *)cur_list->content)->pipeline->command_list;
		while (cmd_node)
		{
			redir_list = ((t_command *)cmd_node->content)->redir_list;
			while (redir_list)
			{
				if (handler((t_redir*)redir_list->content) != 0)
					return (1);
				redir_list = redir_list->next;
			}
			cmd_node = cmd_node->next;
		}
		cur_list = cur_list->next;
	}
	return (0);
}
