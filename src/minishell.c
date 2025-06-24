#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "minishell.h"
#include "signal_handler.h"
#include "utils/ms_stdio.h"
#include "utils/ms_string.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_signal_received = 0; // 定義

static bool				process_option_c(int argc, char **argv, char **envp);
static bool				prompt(char **envp, int *prev_exit_code);
static int				run_cmd(char **input, char **envp, int *prev_exit_code);

int	main(int argc, char **argv, char **envp)
{
	int	prev_exit_code;

	if (setup_signal_handlers() != 0)
		return (EXIT_FAILURE);
	if (process_option_c(argc, argv, envp))
		return (EXIT_SUCCESS);
	if (argc > 1)
	{
		ms_fputs("minishell except only -c flags", STDERR_FILENO);
		return (EXIT_USER_ERR);
	}
	prev_exit_code = 0;
	while (1)
		if (prompt(envp, &prev_exit_code))
			break ;
	return (EXIT_SUCCESS);
}

static bool	process_option_c(int argc, char **argv, char **envp)
{
	if (!(argc == 3 && ms_strcmp(argv[1], "-c") == 0))
		return (false);
	run_cmd(&argv[2], envp, NULL);
	return (true);
}

// TODO: display new line aftter echo -n fire
// return whether it should exit
static bool	prompt(char **envp, int *prev_exit_code)
{
	char	*input_str;

	while (1)
	{
		input_str = readline("minishell$ ");
		if (!input_str)
		{
			printf("exit\n");
			return (true);
		}
		if (!*input_str)
		{
			free(input_str);
			continue ;
		}
		break ;
	}
	*prev_exit_code = run_cmd(&input_str, envp, prev_exit_code);
	if (*input_str)
		add_history(input_str);
	free(input_str);
	return (false);
}

static int	run_cmd(char **input, char **envp, int *prev_exit_code)
{
	t_ast	*ast;
	t_error	*error;
	int		exit_code;

	error = NULL;
	ast = NULL;
	exit_code = EXIT_OK;
	if (!*input)
	{
		printf("\n");
		return (exit_code);
	}
	(void)prev_exit_code; // TODO: pass this to process_expansion!!
	error = str_to_ast(input, &ast);
	if (is_error(error))
	{
		ms_fputs(error->msg, STDERR_FILENO);
		exit_code = error->exit_code;
		del_error(error);
		return (exit_code);
	}
	error = process_expansion(ast);
	if (is_error(error))
	{
		exit_code = error->exit_code;
		ms_fputs(error->msg, STDERR_FILENO);
		free_ast(&ast);
		return (exit_code);
	}
	exit_code = exec_ast(ast, envp);
	free_ast(&ast);
	return (exit_code);
}
