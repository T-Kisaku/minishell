#include "tokenizer.h"
#include "token.h"

t_token_list	*tokenizer(char *string);
static int	tokenize(t_token_list **head, char *string);
static void	init_token_context(t_token_context *tc, t_token_list **head,
				char *string);
static int	tokenize_loop(t_token_context *tc);
static int	add_eof_token(t_token_context *tc);

t_token_list	*tokenizer(char *string)
{
	t_token_list	*head;

	head = NULL;
	if (string == NULL)
	{
		write_error("string is NULL");
		return (NULL);
	}
	if (tokenize(&head, string) != 0)
	{
		clean_token_list(&head);
		return (NULL);
	}
	return (head);
}

static int	tokenize(t_token_list **head, char *string)
{
	t_token_context	tc;

	init_token_context(&tc, head, string);
	if (tokenize_loop(&tc) != 0)
		return (1);
	if (add_eof_token(&tc) != 0)
		return (1);
	return (0);
}

static void	init_token_context(t_token_context *tc, t_token_list **head,
		char *string)
{
	tc->head = head;
	tc->cur_token = NULL;
	tc->start_str = string;
	tc->cur_str = string;
}

static int	tokenize_loop(t_token_context *tc)
{
	while (*tc->cur_str)
	{
		if (ft_isspace(*tc->cur_str))
			process_space(tc);
		else if (*tc->cur_str == '\'' || *tc->cur_str == '"')
		{
			if (process_quoted_word(tc) != 0)
				return (1);
		}
		else if (*tc->cur_str == '<' || *tc->cur_str == '>'
				|| *tc->cur_str == '|')
		{
			if (process_special_char(tc) != 0)
				return (1);
		}
		else
		{
			if (process_unquoted_word(tc) != 0)
				return (1);
		}
	}
	return (0);
}

static int	add_eof_token(t_token_context *tc)
{
	if (create_token(tc) != 0)
		return (1);
	if (set_token(tc, TOKEN_EOF) != 0)
		return (1);
	return (0);
}
