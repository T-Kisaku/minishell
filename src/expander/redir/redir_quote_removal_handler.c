#include "ast.h"
#include "expander.h"

int	redir_quote_removal_handler(t_redir *target)
{
	if (target->type == REDIR_HERE_DOC)//ヒアドクはなにもしない。
		return (0);
	if (target->to.filename_token->type == TOKEN_SINGLE_QUOTED_WORD)
		return (0);//外側がシングルクオートの場合もなにもしない
	if (quote_remove_core(target->to.filename_token) != 0)
		return (1);
	return (0);
}
