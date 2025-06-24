#include "exit_status.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include "error.h"
#include "libft.h"

t_error		*check_quote(char **input);
static int	check_quote_core(char *input);

t_error	*check_quote(char **input)
{
	char	*new_input;
	char	*read_str;
	t_error *error;

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
		new_input = ft_strjoin(*input, read_str);
		free(*input);
		free(read_str);
		*input = new_input;
	}
}

static int	check_quote_core(char *input)
{
	int in_quote;
	char quote;

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