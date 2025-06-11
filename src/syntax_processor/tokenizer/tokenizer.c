#include "tokenizer.h"

t_list	*tokenizer(char *string);
static int	tokenize(t_list **head, char *string);
static void	init_token_context(t_token_context *ctx, t_list **head,
				char *string);
static int	tokenize_loop(t_token_context *ctx);
static int	add_eof_token(t_token_context *ctx);

t_list	*tokenizer(char *string)
{
	t_list	*head;

	head = NULL;
	if (string == NULL)
	{
		write_error("string is NULL");
		return (NULL);
	}
	if (tokenize(&head, string) != 0)
	{
		free_token_list(&head);
		return (NULL);
	}
	return (head);
}

static int	tokenize(t_list **head, char *string)
{
	t_token_context	ctx;

	init_token_context(&ctx, head, string);
	if (tokenize_loop(&ctx) != 0)
		return (1);
	if (add_eof_token(&ctx) != 0)
		return (1);
	return (0);
}

static void	init_token_context(t_token_context *ctx, t_list **head,
		char *string)
{
	ctx->head = head;
	ctx->cur_token = NULL;
	ctx->start_str = string;
	ctx->cur_str = string;
}

static int	tokenize_loop(t_token_context *ctx)
{
	while (*ctx->cur_str)
	{
		if (ft_isspace(*ctx->cur_str))
			process_space(ctx);
		else if (*ctx->cur_str == '\'' || *ctx->cur_str == '"')
		{
			if (process_quoted_word(ctx) != 0)
				return (1);
		}
		else if (*ctx->cur_str == '<' || *ctx->cur_str == '>'
				|| *ctx->cur_str == '|')
		{
			if (process_special_char(ctx) != 0)
				return (1);
		}
		else
		{
			if (process_unquoted_word(ctx) != 0)
				return (1);
		}
	}
	return (0);
}

static int	add_eof_token(t_token_context *ctx)
{
	if (create_token(ctx) != 0)
		return (1);
	if (set_token(ctx, TOKEN_EOF) != 0)
		return (1);
	return (0);
}
