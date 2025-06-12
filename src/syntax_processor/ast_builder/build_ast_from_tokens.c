#include "ast.h"
#include "ast_builder.h"
#include "token.h"
#include "utils/utils.h"
#include <stdlib.h>

int			build_ast_from_tokens(t_list *tokens, t_ast *ast);
static int	return_result(t_list *token, int result);

int	build_ast_from_tokens(t_list *tokens, t_ast *ast)
{
	t_and_or	*and_or;
	int			result;

	and_or = (t_and_or *)ast->content;
	while (tokens)
	{
		if (!and_or->pipeline->command_list)
		{
			if (create_command_list(&and_or->pipeline->command_list) != 0)
				return (1);
		}
		if (!and_or->pipeline->command_list->content)
		{
			if (create_list(&and_or->pipeline->command_list->content))
				return (1);
		}
		result = handle_token_for_ast(tokens, and_or->pipeline->command_list);
		if (result != 0)
			return (return_result(tokens, result));
	}
	return (0);
}

static int	return_result(t_list *token, int result)
{
	if (result == 1)
	{
		free_token_list(&token);
		return (1);
	}
	else if (result == 2)
	{
		free_token_list(&token);
	}
	return (0);
}
