#include "error.h"
#include "expander.h"
#include "utils/utils.h"
#include "utils/env.h"
#include "exit_status.h"

static t_error	*expand_command(t_ast *ast, t_list* env_list);
static t_error	*expand_redir(t_ast *ast, t_list *env_list);

t_error	*expand_ast(t_ast *ast, t_list *env_list)
{
	t_error	*error;

	if (!ast || !env_list)
		return (new_error(EXIT_USER_ERR, "Invalid arguments to expand_ast"));

	error = NULL;
	if (is_error(error))
		return (error);
	error = expand_command(ast, env_list);
	if (is_error(error))
		return (error);
	error = expand_redir(ast, env_list);
	if (is_error(error))
		return (error);
	return (NULL);
}

static t_error	*expand_command(t_ast *ast, t_list *env_list)
{
	t_error	*error;

	error = NULL;
	error = cmd_loop(ast, expand_handler, env_list);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, word_split_handler,env_list);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, quote_removal_handler,env_list);
	if (is_error(error))
		return (error);
	error = cmd_loop(ast, generate_argv_handler, env_list);
	return (error);
}

static t_error	*expand_redir(t_ast *ast, t_list *env_list)
{
	t_error	*error;

	error = NULL;
	error = redir_loop(ast, input_heredoc_content_handler, env_list);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_expand_handler,env_list);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_split_handler,env_list);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, redir_quote_removal_handler,env_list);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, generate_heredoc_file_handler,env_list);
	if (is_error(error))
		return (error);
	error = redir_loop(ast, generate_filename_handler,env_list);
	return (error);
}
