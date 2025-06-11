#include "ast_builder.h"
#include "utils/utils.h"
#include <stdbool.h> //bool,

t_ast		*ast_builder(t_list *tokens);
void		init_command(t_command *cur_cmd);
//subshell, &&, ||については未実装
t_ast	*ast_builder(t_list *tokens)
{
	t_ast			*ast;
	t_and_or		*and_or;
	t_command		*cur_cmd;
	t_token_content	*cur_token_content;
	t_list			*last_token;
	t_list			*next_token;
	t_list			*redir;
	t_redir_type	redir_type;
	int				result;
	t_list			*prev;

	if (!tokens)
		return (1);
	ast = malloc(sizeof(t_ast));
	if (!ast)
	{
		free_all(&tokens, ast);
		return (NULL);
	}
	ast->next = NULL;
	and_or = malloc(sizeof(t_and_or));
	if (!and_or)
	{
		free_all(&tokens, ast);
		return (1);
	}
	and_or = (t_and_or *)ast->content;
	and_or->op_next = OP_NONE;
	and_or->pipeline = malloc(sizeof(t_pipeline));
	if (!and_or->pipeline)
	{
		free_all(&tokens, ast);
		return (1);
	}
	cur_cmd = (t_command *)and_or->pipeline->command_list->content;
	init_command(cur_cmd);
	prev = NULL;
	while (tokens)
	{
		if (and_or->pipeline->command_list)
		{
			if (create_command_list(and_or->pipeline->command_list, prev) != 0)
				return (1);
		}
		cur_token_content = (t_token_content *)tokens->content;
		result = handle_token_for_ast(tokens, and_or->pipeline->command_list);
		if (result == 1)
		{
			free_token_list(&tokens);
			return (1);
		}
		else if (result == 2)
			break ;
		next_token = tokens->next;
		tokens->next = NULL;
		tokens = next_token;
	}
	return (ast);
}

void	init_command(t_command *cur_cmd)
{
	cur_cmd->redir_list = NULL;
	cur_cmd->type = CMD_SIMPLE;
	cur_cmd->u.simple.argc = INT_MIN;
	cur_cmd->u.simple.argv = NULL;
	cur_cmd->u.simple.token_list = NULL;
}

static void	free_all(t_list *tokens, t_ast *ast)
{
	free_token_list(&tokens);
	free_ast(ast);
}

int	create_command_list(t_list *cmd_list, t_list *prev)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!cmd_list)
		return (1);
	if (!prev)
		cmd_list = new;
	else
	{
		
		prev
	}
	return (0);
}
