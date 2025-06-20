#include "libft.h"
#include "syntax_processor.h"
#include "syntax_processor/check_syntax/check_syntax.h"
#include "token.h"
#include "utils/utils.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

#define SYNTAX_OK 2

int			check_syntax(t_list *list);
static int	check_head(t_list **cur, t_list **prev);
static int	check_body(t_list **cur, t_list **prev);
static int	check_syntax_pair(e_token_group cur, e_token_group prev);
static int	check_tail(t_list *tail);
static int	set_token_group(e_token_group *group, e_token_type type);

int	check_syntax(t_list *list)
{
	t_list	*cur;
	t_list	*prev;
	int		result;

	if (!list)
		return (1);
	cur = list;
	prev = NULL;
	if (check_head(&cur, &prev) != 0)
		return (1);
	while (1)
	{
		if (check_body(&cur, &prev) != 0)
			return (1);
		result = check_tail(prev);
		if (result == 0)
			cur = prev->next;
		else if (result == 1)
			return (1);
		else if (result == SYNTAX_OK)
			return (0);
	}
}

static int	check_head(t_list **cur, t_list **prev)
{
	e_token_group	cur_group;

	if (set_token_group(&cur_group,
						((t_token_content *)(*cur)->content)->type) != 0)
		return (write_error("bad token group"));
	if (cur_group == TOKEN_GROUP_CONTROL_OP)
		return (syntax_error(((t_token_content *)(*cur)->content)->value));
	(*prev) = (*cur);
	(*cur) = (*cur)->next;
	return (0);
}

static int	check_body(t_list **cur, t_list **prev)
{
	e_token_group	cur_group;
	e_token_group	prev_group;

	if (set_token_group(&prev_group,
						((t_token_content *)(*prev)->content)->type))
		return (write_error("bad token group"));
	while (*cur)
	{
		if (set_token_group(&cur_group,
							((t_token_content *)(*cur)->content)->type))
			return (write_error("bad token group"));
		if (check_syntax_pair(cur_group, prev_group) != 0)
			return (syntax_error(((t_token_content *)(*cur)->content)->value));
		(*prev) = (*cur);
		prev_group = cur_group;
		(*cur) = (*cur)->next;
	}
	return (0);
}

static int	check_syntax_pair(e_token_group cur, e_token_group prev)
{
	if (prev == TOKEN_GROUP_REDIR)
	{
		if (cur != TOKEN_GROUP_WORD)
			return (1);
	}
	else if (prev == TOKEN_GROUP_CONTROL_OP)
	{
		if (cur == TOKEN_GROUP_CONTROL_OP)
			return (1);
	}
	return (0);
}

static int	check_tail(t_list *tail)
{
	e_token_group	group;
	char			*input;
	t_list			*new;

	if (set_token_group(&group, ((t_token_content *)tail->content)->type) != 0)
		return (write_error("bad token group"));
	if (group == TOKEN_GROUP_CONTROL_OP)
	{
		input = readline("> ");
		new = tokenizer(input);
		if (!new)
			return (1);
		tail->next = new;
		return (0);
	}
	else if (group == TOKEN_GROUP_REDIR)
		return (syntax_error(((t_token_content *)tail->content)->value));
	else if (group == TOKEN_GROUP_WORD)
		return (SYNTAX_OK);
	else
		return (write_error("bad token group"));
}

static int	set_token_group(e_token_group *group, e_token_type type)
{
	if (is_word_token(type))
	{
		*group = TOKEN_GROUP_WORD;
		return (0);
	}
	else if (is_redir_token(type))
	{
		*group = TOKEN_GROUP_REDIR;
		return (0);
	}
	else if (is_control_op_token(type))
	{
		*group = TOKEN_GROUP_CONTROL_OP;
		return (0);
	}
	else
		return (1);
}
