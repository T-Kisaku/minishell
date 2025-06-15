#include "syntax_processor/tokenizer.h"

int		write_error(char *msg);

//always return (1);
int	write_error(char *msg)
{
	char	*prefix;

	prefix = "minishell: ";
	write(2, prefix, ft_strlen(prefix));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}


