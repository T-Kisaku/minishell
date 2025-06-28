#include "error.h"
#include "expander.h"
#include "utils/utils.h"
#include "utils/env.h"
#include "exit_status.h"
#include "minishell.h"

static t_error	*expand_command(t_ast *ast, t_minishell_state *shell);
static t_error	*expand_redir(t_ast *ast, t_minishell_state *shell);

t_error	*expand_ast(t_ast *ast, t_minishell_state *shell)
{
	t_error	*error;

	if (!ast || !shell)
		return (new_error(EXIT_USER_ERR, "Invalid arguments to expand_ast"));

	error = NULL;
	if (is_error(error))
		return (error);
	error = expand_command(ast, shell);
	if (is_error(error))
		return (error);
	error = expand_redir(ast, shell);
	if (is_error(error))
		return (error);
	return (NULL);
}

static t_error	*expand_command(t_ast *ast, t_minishell_state *shell)
{
	t_error	*error;

	error = NULL;
	error = cmd_loop(ast, expand_handler, shell);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, word_split_handler,shell);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, quote_removal_handler,shell);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, generate_argv_handler, shell);
	return (error);
}

static t_error	*expand_redir(t_ast *ast, t_minishell_state *shell)
{
	t_error	*error;

	error = NULL;
	error = redir_loop(ast, input_heredoc_content_handler, shell);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_expand_handler,shell);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_split_handler,shell);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_quote_removal_handler,shell);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, generate_heredoc_file_handler,shell);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, generate_filename_handler,shell);
	return (error);
}
