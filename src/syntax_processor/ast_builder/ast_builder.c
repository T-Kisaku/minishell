#include "ast_builder.h"

//subshell, &&, ||については未実装
t_ast	*ast_builder(t_list *tokens)
{
	t_ast	*ast;
	

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->next = NULL;
	ast->first_and_or = malloc(sizeof(t_and_or));
	if (!ast->first_and_or)
	{
		free(ast);
		return (1);
	}
	ast->first_and_or->op_next = OP_NONE;
	ast->first_and_or->next = NULL;
	ast->first_and_or->pipeline return (ast);
}

void	free_ast(t_ast *ast)
{
	t_ast *cur;
	if (!ast)
		return ;
	cur = ast;
	while (cur)
	{
		while(cur->)
		cur = cur->next;
	}
}