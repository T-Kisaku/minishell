#include "../../include/lexer.h"

void	process_spaces(t_lexer_context *lc);
int		process_quoted(t_lexer_context *lc, e_segment_type seg_type);
int		process_unquoted(t_lexer_context *lc);
int	set_segment_value(t_lexer_context *lc, e_segment_type type);

void process_space(t_lexer_context *lc)
{
	while(ft_isspace(*lc->cur_str))
		lc->cur_str++;
	lc->start_str = lc->cur_str;
	lc->need_new_token = true;
}

//unquoted string
int	process_unquoted(t_lexer_context *lc)
{
	if(ensure_token_and_segment(lc) != 0)
		return (1);
	while (*lc->cur_str != '\0' && !ft_isspace(*lc->cur_str)
		&& *lc->cur_str != '\'' && *lc->cur_str != '"' && *lc->cur_str != '|'
		&& *lc->cur_str != '<' && *lc->cur_str != '>')
		lc->cur_str++;
	if (set_segment_value(lc, UNQUOTED_WORD) != 0)
		return (1);
	return (0);
}

//quoted string
int	process_quoted(t_lexer_context *lc, e_segment_type seg_type)
{
	char	quote;

	if(ensure_token_and_segment(lc) != 0)
		return (1);
	lc->cur_str++;
	lc->start_str = lc->cur_str;
	if (seg_type == SINGLE_QUOTED_WORD)
		quote = '\'';
	else if (seg_type == DOUBLE_QUOTED_WORD)
		quote = '"';
	else
		return (write_error("bad segment_type on process_in_quote"));
	while (*lc->cur_str != '\0' && *lc->cur_str != quote)
		lc->cur_str++;
	if (*lc->cur_str == '\0')
		return (write_error("unclosed quotes"));
	if (set_segment_value(lc, seg_type) != 0)
		return (1);
	lc->cur_str++;
	lc->start_str = lc->cur_str;
	return (0);
}

int	set_segment_value(t_lexer_context *lc, e_segment_type type)
{
	lc->cur_seg->value = malloc(sizeof(char) *
								(lc->cur_str - lc->start_str + 1));
	if (!lc->cur_seg->value)
		return (write_error("malloc error \"value\""));
	ft_memcpy(lc->cur_seg->value, lc->start_str, lc->cur_str - lc->start_str);
	lc->cur_seg->value[lc->cur_str - lc->start_str] = '\0';
	lc->cur_seg->type = type;
	lc->prev_seg = lc->cur_seg;
	lc->start_str = lc->cur_str;
	return (0);
}
