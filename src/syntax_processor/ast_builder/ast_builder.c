#include "ast_builder.h"

static void	free_command(t_command **cmd);
//subshell, &&, ||については未実装
t_ast	*ast_builder(t_list *tokens)
{
	t_ast			*ast;
	t_and_or		*and_or;
	t_command		*cur_cmd;
	t_token_content	*cur_token_content;
	t_list			*last_token;
	t_list			*next_token;

	and_or = (t_and_or *)ast->content;
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->next = NULL;
	and_or = malloc(sizeof(t_and_or));
	if (!and_or)
	{
		free(ast);
		return (1);
	}
	and_or->op_next = OP_NONE;
	and_or->pipeline = malloc(sizeof(t_pipeline));
	if (!and_or->pipeline)
	{
		free(and_or);
		free(ast);
		return (1);
	}
	cur_cmd = (t_command *)and_or->pipeline->command_list->content;
	cur_cmd->redir_list = NULL;
	cur_cmd->type = CMD_SIMPLE;
	cur_cmd->u.simple.argc = INT_MIN;
	cur_cmd->u.simple.argv = NULL;
	cur_cmd->u.simple.token_list = NULL;
	while (tokens)
	{
		cur_token_content = (t_token_content *)tokens->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD
			|| cur_token_content->type == TOKEN_SINGLE_QUOTED_WORD
			|| cur_token_content->type == TOKEN_DOUBLE_QUOTED_WORD)
		{
			last_token = ft_lstlast(cur_cmd->u.simple.token_list);
			if (last_token)
				last_token->next = tokens;
			else
				cur_cmd->u.simple.token_list = tokens;
		}
		else if (cur_token_content->type = TOKEN_PIPE)
		{
			and_or->pipeline->command_list->next = malloc(sizeof(t_list *));
			if (!and_or->pipeline->command_list->next)
			{
				free_
			}
		}
		next_token = tokens->next;
		tokens->next = NULL;
		tokens = next_token;
	}
	return (ast);
}

static int	init_command(t_command *cur_cmd)
{
}




