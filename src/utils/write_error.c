#include "libft.h"
#include <stddef.h>
#include <unistd.h>

int	write_error(char *msg);
int	syntax_error(const char *token);

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
//always return(1);
int	syntax_error(const char *token)
{
	const char	*prefix;
	const char	*suffix;

	prefix = "minishell: syntax error near unexpected token `";
	suffix = "'\n";
	write(2, prefix, ft_strlen(prefix));
	write(2, token, ft_strlen(token));
	write(2, suffix, ft_strlen(suffix));
	return (1);
}
