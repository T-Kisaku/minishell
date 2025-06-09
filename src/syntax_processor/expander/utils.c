#include "../../../include/ast.h"
#include "../../../include/expander.h"
#include "../../../libft/libft.h"

int		cmd_loop(t_ast *ast, int (*handler)(t_command *));
void	free_argv(char ***argv, int num);
void	copy_and_advance(t_expansion_context *ctx, char *src, size_t count);

int	cmd_loop(t_ast *ast, int (*handler)(t_command *))
{
	t_a_list	*cur_list;
	t_and_or	*cur_and_or;
	int			cmd_index;

	if (!ast || !handler)
		return (1);
	cur_list = ast;
	while (cur_list)
	{
		cur_and_or = cur_list->first_and_or;
		while (cur_and_or)
		{
			cmd_index = 0;
			while (cmd_index < cur_and_or->pipeline.cmd_count)
			{
				if (handler(&cur_and_or->pipeline.commands[cmd_index]) != 0)
					return (1);
				cmd_index++;
			}
			cur_and_or = cur_and_or->next;
		}
		cur_list = cur_list->next;
	}
	return (0);
}

void	free_argv(char ***argv, int num)
{
	int	i;

	if (!argv || !*argv)
		return ;
	i = 0;
	if (num == INT_MAX)
		while ((*argv)[i])
		{
			free((*argv)[i]);
			(*argv)[i] = NULL;
			i++;
		}
	else
	{
		while (i < num)
		{
			free((*argv)[i]);
			(*argv)[i] = NULL;
			i++;
		}
	}
	free(*argv);
	*argv = NULL;
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
