#include "syntax_processor/tokenizer.h"

int			process_special_char(t_token_context *ctx);
static int	process_less_than(t_token_context *ctx);
static int	process_greater_than(t_token_context *ctx);

int	process_special_char(t_token_context *ctx)
{
	if (create_token(ctx) != 0)
		return (1);
	if (*ctx->cur_str == '<')
		return (process_less_than(ctx));
	else if (*ctx->cur_str == '>')
		return (process_greater_than(ctx));
	else if (*ctx->cur_str == '|')
	{
		ctx->cur_str++;
		return (set_token(ctx, TOKEN_PIPE));
	}
	return (0);
}

// "<" or "<<"
static int	process_less_than(t_token_context *ctx)
{
	ctx->cur_str++;
	if (*ctx->cur_str != '<')
		return (set_token(ctx, TOKEN_REDIR_INPUT));
	else if (*ctx->cur_str == '<')
	{
		ctx->cur_str++;
		return (set_token(ctx, TOKEN_REDIR_HERE_DOC));
	}
	return (0);
}

//">" or ">>"
static int	process_greater_than(t_token_context *ctx)
{
	ctx->cur_str++;
	if (*ctx->cur_str != '>')
		return (set_token(ctx, TOKEN_REDIR_OUTPUT));
	else if (*ctx->cur_str == '>')
	{
		ctx->cur_str++;
		return (set_token(ctx, TOKEN_REDIR_APPEND));
	}
	return (0);
}
