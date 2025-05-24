#include "../../include/lexer.h"

int	process_special_char(t_lexer_context *lc);
static int	process_less_than(t_lexer_context *lc);
static int	process_greater_than(t_lexer_context *lc);

int	process_special_char(t_lexer_context *lc)
{
	lc->need_new_token = true;
	if(ensure_token_and_segment(lc) != 0)
		return (1);
	lc->need_new_token = true;//in ensure_token_and_segment, be false;
	if (*lc->cur_str == '<')
		return (process_less_than(lc));
	else if (*lc->cur_str == '>')
		return (process_greater_than(lc));
	else if (*lc->cur_str == '|')
	{
		lc->cur_str++;
		if (*lc->cur_str == '|')
			return (syntax_error(lc->start_str, 2));
		else
			return (set_segment_value(lc, UNQUOTED_WORD));
	}
	return (0);
}

//"<"" and "<<"" are one token. "<>" is two tokens.
static int	process_less_than(t_lexer_context *lc)
{
	lc->cur_str++;
	if (*lc->cur_str == '<')
	{
		lc->cur_str++;
		if (*lc->cur_str == '<' || *lc->cur_str == '>')
			return (syntax_error(lc->cur_str, 1));
		return (set_segment_value(lc, UNQUOTED_WORD));
	}
	else if (*lc->cur_str == '>')
	{
		lc->cur_str++;
		if (*lc->cur_str == '<' || *lc->cur_str == '>')
			return (syntax_error(lc->cur_str, 1));
		lc->cur_str = lc->start_str + 1;
		if (set_segment_value(lc, UNQUOTED_WORD) != 0)
			return (1);
		if(ensure_token_and_segment(lc) != 0)
			return (1);
		lc->need_new_token = true;
		lc->cur_str = lc->start_str + 1;
		return (set_segment_value(lc, UNQUOTED_WORD));
	}
	else
		return (set_segment_value(lc, UNQUOTED_WORD));
}

//">" and ">>" are one token.
static int	process_greater_than(t_lexer_context *lc)
{
	lc->cur_str++;
	if (*lc->cur_str == '<')
		return (syntax_error(lc->cur_str, 1));
	else if (*lc->cur_str == '>')
	{
		lc->cur_str++;
		if (*lc->cur_str == '<' || *lc->cur_str == '>')
			return (syntax_error(lc->cur_str, 1));
		else
			return (set_segment_value(lc, UNQUOTED_WORD));
	}
	else
		return (set_segment_value(lc, UNQUOTED_WORD));
}
