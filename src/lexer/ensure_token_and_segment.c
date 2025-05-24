#include "../../include/lexer.h"

int			ensure_token_and_segment(t_lexer_context *lc);
static int	get_new_token(t_lexer_context *lc);
static int	get_new_segment(t_lexer_context *lc);

int	ensure_token_and_segment(t_lexer_context *lc)
{
	if (lc->need_new_token)
	{
		if (get_new_token(lc) != 0)
			return (1);
	}
	return (get_new_segment(lc));
}

static int	get_new_token(t_lexer_context *lc)
{
	lc->prev_token = lc->cur_token;
	lc->cur_token = malloc(sizeof(t_token));
	if (!lc->cur_token)
		return (write_error("malloc error \"cur_token\""));
	if (*lc->head == NULL)
		*lc->head = lc->cur_token;
	lc->need_new_token = false;
	lc->cur_token->next = NULL;
	lc->cur_token->segments = NULL;
	if (lc->prev_token)
		lc->prev_token->next = lc->cur_token;
	lc->prev_seg = NULL;
	return (0);
}

static int	get_new_segment(t_lexer_context *lc)
{
	lc->cur_seg = malloc(sizeof(t_segment));
	if (!lc->cur_seg)
		return (write_error("malloc error \"cur_seg\""));
	if (lc->prev_seg)
		lc->prev_seg->next = lc->cur_seg;
	else
		lc->cur_token->segments = lc->cur_seg;
	lc->cur_seg->next = NULL;
	lc->cur_seg->value = NULL;
	lc->prev_seg = lc->cur_seg;
	return (0);
}
