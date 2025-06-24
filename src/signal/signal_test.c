#include "libft.h"
#include "minishell.h"
#include "signal_handler.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0;

int	main(void)
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
		input = readline("test> ");
		puts(input);
		if (input == NULL)
		{
			free(input);
			printf("exit\n");
			exit(0);
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		// printf("%zu: %s\n", ft_strlen(input), input);
		if (ft_strlen(input) == 5 && ft_strncmp(input, "start", 5) == 0)
		{
			free(input);
			while (1)
			{
				input = readline("> ");
				if (input == NULL)
				{
					printf("No input received, exiting...\n");
					free(input);
					return (0);
				}
				if (ft_strlen(input) == 3 && ft_strncmp(input, "end", 3) == 0)
				{
					free(input);
					break ;
				}
				free(input);
			}
			continue ;
		}
		else if (ft_strlen(input) == 4 && ft_strncmp(input, "exit", 4) == 0)
		{
			free(input);
			printf("Exiting...\n");
			break ;
		}
		else
		{
			printf("You entered: %s\n", input);
			free(input);
		}
	}
	return (0);
}
