#include "../../../include/ast.h"
#include "../../../include/expander.h"
#include "../../../include/token.h"
#include "../../../include/utils.h"
#include "../../../libft/libft.h"

int	split_token(t_token_list *token, int word_count);
static int	init_split_token_context(t_split_token_context *ctx, t_token_list *token);
static int	generate_value(t_split_token_context *ctx);
int	generate_token(t_split_token_context *ctx);

int	split_token(t_token_list *token, int word_count)
{
	t_split_token_context	ctx;

	init_split_token_context(&ctx, token);
	free(token->content->value);
	if (generate_value(&ctx) != 0)
	{
		free(ctx.original);
		return (1);
	}
	while (--word_count)
	{
		if (generate_token(&ctx) != 0)
		{
			free(ctx.original);
			return (1);
		}
	}
	free(ctx.original);
	return (0);
}

static int	init_split_token_context(t_split_token_context *ctx, t_token_list *token)
{
	ctx->cur = token;
	ctx->next = token->next;
	ctx->tmp = NULL;
	ctx->original = ft_strdup(ctx->cur->content->value);
	if (!ctx->original)
		return (1);
	ctx->start_str = ctx->original;
	ctx->cur_str = ctx->original;
	return (0);
}

static int	generate_value(t_split_token_context *ctx)
{
	while (*ctx->cur_str && ft_isspace(*ctx->cur_str))
		ctx->cur_str++;
	ctx->start_str = ctx->cur_str;
	while (*ctx->cur_str && !ft_isspace(*ctx->cur_str))
		ctx->cur_str++;
	ctx->cur->content->value = malloc(sizeof(char) * (ctx->cur_str
				- ctx->start_str + 1));
	if (!ctx->cur->content->value)
		return (1);
	ft_memcpy((char *)ctx->cur->content->value, (char *)ctx->start_str,
			ctx->cur_str - ctx->start_str);
	ctx->cur->content->value[ctx->cur_str - ctx->start_str] = '\0';
	return (0);
}

int	generate_token(t_split_token_context *ctx)
{
	ctx->tmp = malloc(sizeof(t_token_list));
	if (!ctx->tmp)
		return (1);
	ctx->cur->next = ctx->tmp;
	ctx->tmp->next = ctx->next;
	ctx->cur = ctx->tmp;
	ctx->next = ctx->cur->next;
	ctx->cur->content = malloc(sizeof(t_token_content));
	if (!ctx->cur->content)
		return (1);
	ctx->cur->content->type = TOKEN_UNQUOTED_WORD;
	if (generate_value(ctx) != 0)
		return (1);
	return (0);
}
