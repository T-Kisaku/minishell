#include "../../include/lexer.h"

int			tokenize(t_token **head, char *string);
static void	init_lexer_context(t_lexer_context *lc, t_token **head,
				char *string);

int	tokenize(t_token **head, char *string)
{
	t_lexer_context	lc;

	init_lexer_context(&lc, head, string);
	while (*lc.cur_str)
	{
		if (ft_isspace(*lc.cur_str))
			process_space(&lc);
		else if (*lc.cur_str == '\'')
		{
			if (process_quoted(&lc, SINGLE_QUOTED_WORD) != 0)
				return (1);
		}
		else if (*lc.cur_str == '"')
		{
			if (process_quoted(&lc, DOUBLE_QUOTED_WORD) != 0)
				return (1);
		}
		else if (*lc.cur_str == '<' || *lc.cur_str == '>' || *lc.cur_str == '|')
		{
			if (process_special_char(&lc) != 0)
				return (1);
		}
		else
		{
			if (process_unquoted(&lc) != 0)
				return (1);
		}
	}
	return 0;
}

static void	init_lexer_context(t_lexer_context *lc, t_token **head,
		char *string)
{
	lc->head = head;
	lc->cur_token = NULL;
	lc->prev_token = NULL;
	lc->cur_seg = NULL;
	lc->prev_seg = NULL;
	lc->start_str = string;
	lc->cur_str = string;
	lc->need_new_token = true;
}
