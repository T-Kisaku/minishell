#include "../../../include/ast.h"
#include "../../../include/expander.h"

int			process_expansion(t_ast *ast);
int			expand_tokens_handler(t_command *cmd);
static int	expand_token_list(t_token_list **tokens);

int	process_expansion(t_ast *ast)
{
	if (cmd_loop(ast, expand_handler) != 0) //４つのうち上３つの関数でredirsのchar*にも同様のことを行う。
		return (1);
	if (cmd_loop(ast, word_split_handler) != 0)
		return (1);
	if (cmd_loop(ast, quote_removal_handler) != 0)
		return (1);
	if (cmd_loop(ast, generate_argv_handler) != 0)
		return (1);
	// if (cmd_loop(ast, generate_heredoc_file)!= 0) ここでheredocの１時ファイルを作成する。
	// 	return (1);
	return (0);
}

int	expand_tokens_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (expand_token_list(&cmd->u.simple.token_list) != 0)
			return (1);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		if (process_expansion(cmd->u.subshell.list) != 0)
			return (1);
	}
	return (0);
}

static int	expand_token_list(t_token_list **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->content->type == TOKEN_UNQUOTED_WORD
			|| (*tokens)->content->type == TOKEN_DOUBLE_QUOTED_WORD)
		{
			if (expand_single_token(tokens) != 0)
				return (1);
		}
		tokens = &(*tokens)->next;
	}
	return (0);
}
