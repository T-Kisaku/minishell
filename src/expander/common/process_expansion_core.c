#include "expander.h"

int	process_expansion_core_core(t_expansion_context *ctx,
								e_expander_mode mode);
static int	process_expansion_core_core_core(t_expansion_context *ctx,
											int (*func)(t_expansion_context *),
											e_expander_mode mode);

int	process_expansion_core_core(t_expansion_context *ctx,
								e_expander_mode mode)
{
	if (ctx->cur_dollar_type == DOLLAR_SPECIAL)
	{
		if (process_expansion_core_core_core(ctx, expand_special, mode) != 0)
			return (1);
	}
	else if (ctx->cur_dollar_type == DOLLAR_VARIABLE)
	{
		if (process_expansion_core_core_core(ctx, expand_variable, mode) != 0)
			return (1);
	}
	else if (ctx->cur_dollar_type == DOLLAR_LITERAL && mode == MODE_SET_VALUE)
		copy_and_advance(ctx, --ctx->cur_pos, 1);
	return (0);
}

static int	process_expansion_core_core_core(t_expansion_context *ctx,
											int (*func)(t_expansion_context *),
											e_expander_mode mode)
{
	int	len;

	if (func(ctx) != 0)
	{
		free(ctx->variable);
		ctx->variable = NULL;
		return (1);
	}
	len = ft_strlen(ctx->variable);
	if (mode == MODE_SET_VALUE && len > 0)
		ft_memcpy(&ctx->output[ctx->index], ctx->variable, len);
	ctx->index += len;
	free(ctx->variable);
	ctx->variable = NULL;
	return (0);
}
