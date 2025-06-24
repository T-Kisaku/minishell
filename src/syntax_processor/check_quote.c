#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

t_error		*check_quote(char **input);
static int	check_quote_core(char *input);

t_error	*check_quote(char **input)
{
	char	*new_input;
	char	*read_str;
	char	*temp;
	t_error	*error;

	error = NULL;
	while (1)
	{
		if (check_quote_core(*input) == EXIT_OK)
			return (error);
		read_str = readline("> ");
		if (!read_str)
		{
			printf("exit\n");
			exit(EXIT_OK);
		}
		if (!*read_str)
		{
			free(read_str);
			continue ;
		}
		new_input = ft_strjoin(*input, "\n");
		free(*input);
		if (!new_input)
			return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
		temp = new_input;
		new_input = ft_strjoin(new_input, read_str);
		free(read_str);
		free(temp);
		if (!new_input)
			return (new_error(EXIT_INTERNAL_ERR, "Memory allocation failed"));
		*input = new_input;
	}
}

static int	check_quote_core(char *input)
{
	int		in_quote;
	char	quote;

	in_quote = 0;
	while (*input)
	{
		if (in_quote)
		{
			if (*input == quote)
				in_quote = 0;
		}
		else
		{
			if (*input == '\'' || *input == '"')
			{
				in_quote = 1;
				quote = *input;
			}
		}
		input++;
	}
	if (in_quote)
		return (EXIT_USER_ERR);
	return (EXIT_OK);
}
