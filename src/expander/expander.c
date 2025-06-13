#include "expander.h"


int			process_expansion(t_ast *ast);
int			expand_handler(t_command *cmd);
static int	expand_token_list(t_list **tokens);
static int	generate_filename(t_command *cmd);

int	process_expansion(t_ast *ast)
{
	if (cmd_loop(ast, expand_handler) != 0)
		//４つのうち上３つの関数でredirsのchar*にも同様のことを行う。
		return (1);
	if (cmd_loop(ast, word_split_handler) != 0)
		return (1);
	if (cmd_loop(ast, quote_removal_handler) != 0)
		return (1);
	if (cmd_loop(ast, generate_argv_handler) != 0)
		return (1);
	if (cmd_loop(ast, generate_filename) != 0)
		return (1);
	// if (cmd_loop(ast, generate_heredoc_file)!= 0) ここでheredocの１時ファイルを作成する。
	// 	return (1);
	return (0);
}

int	expand_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (expand_token_list(&cmd->u.simple.token_list) != 0)
			return (1);
	}
	else if (cmd->type == CMD_SUBSHELL)
	{
		if (process_expansion(cmd->u.subshell.and_or_list) != 0)
			return (1);
	}
	return (0);
}

static int	expand_token_list(t_list **tokens)
{
	t_list			*cur_token;
	t_token_content	*cur_token_content;

	cur_token = *tokens;
	while (cur_token)
	{
		cur_token_content = (t_token_content *)cur_token->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD
			|| cur_token_content->type == TOKEN_DOUBLE_QUOTED_WORD)
		{
			if (expand_single_token(&cur_token) != 0)
				return (1);
		}
		cur_token = cur_token->next;
	}
	return (0);
}

int expand_target(t_redir_target *target){
	if(target->is_direct_to_fd)
		return EXIT_SUCCESS;
	target->filename = ft_strdup(target->filename_token->value);
	if(!target->filename)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
static int	generate_filename(t_command *cmd)
{
	t_list			*cur_redir_list;
	t_redir			*redir_content;

	cur_redir_list = cmd->redir_list;
	while (cur_redir_list)
	{
		redir_content = lstget_redir(cur_redir_list);
		if(expand_target(&redir_content->from) == EXIT_FAILURE)
			return EXIT_FAILURE;
		if(expand_target(&redir_content->to) == EXIT_FAILURE)
			return EXIT_FAILURE;
		cur_redir_list = cur_redir_list->next;
	}
	return (EXIT_SUCCESS);
}
