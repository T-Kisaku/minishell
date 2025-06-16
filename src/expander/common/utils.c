#include "expander.h"

int		cmd_loop(t_ast *ast, int (*handler)(t_command *));
int	redir_loop(t_ast *ast, int (*handler)(t_redir *));
void	copy_and_advance(t_expansion_context *ctx, char *src, int count);





void	copy_and_advance(t_expansion_context *ctx, char *src, int count)
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
