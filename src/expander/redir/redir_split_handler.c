#include "ast.h"
#include "token.h"
#include "utils/ms_string.h"
int	redir_split_handler(t_redir *redir);
static int	check_could_not_split(char *value);

int	redir_split_handler(t_redir *redir)
{
	if (redir->type == REDIR_HERE_DOC)
		return (0);
	if (redir->to.filename_token->type == TOKEN_UNQUOTED_WORD)
	{
		if (check_could_not_split(redir->to.filename_token->value) != 0)
			return (1);
	}
	return (0);
}

static int	check_could_not_split(char *value)
{
	char	*cur;

	cur = value;
	while (*value)
	{
		if (ms_isspace(*value))
			return (1); //bashではエラーになる
		value++;
	}
	return (0);
}
