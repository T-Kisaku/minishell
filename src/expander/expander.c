#include "expander.h"
#include "utils/utils.h"

int			process_expansion(t_ast *ast);
static int	expand_command(t_ast *ast);
static int	expand_redir(t_ast *ast);

int	process_expansion(t_ast *ast)
{
	if (expand_command(ast) != 0)
		return (1);
	if (expand_redir(ast) != 0)
		return (1);
	return (0);
}
static int	expand_command(t_ast *ast)
{
	if (cmd_loop(ast, expand_handler) != 0)
		return (1);
	if (cmd_loop(ast, word_split_handler) != 0)
		return (1);
	if (cmd_loop(ast, quote_removal_handler) != 0)
		return (1);
	if (cmd_loop(ast, generate_argv_handler) != 0)
		return (1);
}

static int	expand_redir(t_ast *ast)
{
	if (redir_loop(ast, input_heredoc_content_handler) != 0)
		return (1);
	if (redir_loop(ast, reidr_expand_handler) != 0)
		return (1);
	if (redir_loop(ast, redir_split_handler) != 0)
		return (1);
	if (redir_loop(ast, redir_quote_removal_handler) != 0)
		return (1);
	if (redir_loop(ast, generate_heredoc_file_handler) != 0)
		return (1);
	if (redir_loop(ast, generate_filename_handler) != 0)
		return (1);
}

