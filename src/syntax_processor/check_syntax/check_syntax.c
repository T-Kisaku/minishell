#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "syntax_processor.h"
#include "syntax_processor/check_syntax/check_syntax.h"
#include "token.h"
#include "utils/utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

t_error			*check_syntax(t_list **list);
static t_error	*check_head(t_list **cur, t_list **prev);
static t_error	*check_body(t_list **cur, t_list **prev);
static t_error	*check_syntax_pair(e_token_group cur, e_token_group prev);
static t_error	*check_tail(t_list **list);
static t_error	*set_token_group(e_token_group *group, t_token_type type);

t_error	*check_syntax(t_list **list)
{
	t_error	*error;
	t_list	*cur;
	t_list	*prev;

	if (!list)
		return (new_error(EXIT_INTERNAL_ERR, "list is NULL"));
	cur = *list;
	prev = NULL;
	error = check_head(&cur, &prev);
	if (error)
		return (error);
	error = check_body(&cur, &prev);
	if (error)
		return (error);
	return (check_tail(list));
}

static t_error	*check_head(t_list **cur, t_list **prev)
{
	e_token_group	cur_group;
	t_error			*error;

	error = set_token_group(&cur_group,
							((t_token *)(*cur)->content)->type);
	if (error)
		return (error);
	if (cur_group == TOKEN_GROUP_CONTROL_OP)
		return (new_error(EXIT_USER_ERR,
							"syntax error: unexpected token at the beginning"));
	(*prev) = (*cur);
	(*cur) = (*cur)->next;
	return (error);
}

static t_error	*check_body(t_list **cur, t_list **prev)
{
	e_token_group	cur_group;
	e_token_group	prev_group;
	t_error			*error;

	error = set_token_group(&prev_group,
							((t_token *)(*prev)->content)->type);
	if (error)
		return (error);
	while (*cur)
	{
		error = set_token_group(&cur_group,
								((t_token *)(*cur)->content)->type);
		if (error)
			return (error);
		error = check_syntax_pair(cur_group, prev_group);
		if (error)
			return (error);
		(*prev) = (*cur);
		prev_group = cur_group;
		(*cur) = (*cur)->next;
	}
	return (error);
}

static t_error	*check_syntax_pair(e_token_group cur, e_token_group prev)
{
	t_error	*error;

	error = NULL;
	if (prev == TOKEN_GROUP_REDIR)
	{
		if (cur != TOKEN_GROUP_WORD)
			return (new_error(EXIT_USER_ERR,
								"syntax error: unexpected token after redirection"));
	}
	else if (prev == TOKEN_GROUP_CONTROL_OP)
	{
		if (cur == TOKEN_GROUP_CONTROL_OP)
			return (new_error(EXIT_USER_ERR,
								"syntax error: unexpected token after control operator"));
	}
	return (error);
}

static t_error	*check_tail(t_list **list)
{
	t_error			*error;
	e_token_group	group;
	char			*input;
	t_list			*new;
	t_list			*tail;

	tail = ft_lstlast(*list);
	if (!tail)
		return (new_error(EXIT_INTERNAL_ERR, "list is empty"));
	new = NULL;
	error = set_token_group(&group, ((t_token *)tail->content)->type);
	if (error)
		return (error);
	if (group == TOKEN_GROUP_CONTROL_OP)
	{
		while (1)
		{
			input = readline("> ");
			if (!input)
				return (new_error(EXIT_EOF, "exit"));
			else if (!*input)
			{
				free(input);
				continue ;
			}
			error = str_to_token(input, &new);
			free(input);
			if (error)
			{
				if (new)
					lstclear_token(&new);
				return (error);
			}
			error = check_syntax(&new);
			if (error)
			{
				if (new)
					lstclear_token(&new);
				return (error);
			}
			tail->next = new;
			return (NULL);
		}
	}
	else if (group == TOKEN_GROUP_REDIR)
		return (new_error(EXIT_USER_ERR,
							"syntax error: unexpected token at the end of input"));
	else if (group == TOKEN_GROUP_WORD)
		return (error);
	else
		return (new_error(EXIT_INTERNAL_ERR,
							"syntax error: token group not set"));
}

static t_error	*set_token_group(e_token_group *group, t_token_type type)
{
	t_error	*error;

	error = NULL;
	if (is_word_token(type))
	{
		*group = TOKEN_GROUP_WORD;
		return (error);
	}
	else if (is_redir_token(type))
	{
		*group = TOKEN_GROUP_REDIR;
		return (error);
	}
	else if (is_control_op_token(type))
	{
		*group = TOKEN_GROUP_CONTROL_OP;
		return (error);
	}
	else
		return (new_error(EXIT_INTERNAL_ERR, "token group not set"));
}
