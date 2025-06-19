#include "ast.h"
#include "syntax_processor.h"
#include "expander/expander.h"
#include "token.h"
#include "utils/utils.h"
#include <stdio.h>
int	testcase(char *s);
int	print_core(t_command *cmd);
int	print(t_ast *ast);

int	main(void)
{
	testcase("cat <<abc >aaa.txt");
	return 0;
}

int	testcase(char *s)
{
	t_ast	*ast;
	t_list	*list;

	list = tokenizer(s);
	ast = ast_builder(&list);
	process_expansion(ast);
	print(ast);
	free_ast(&ast);
	return (0);
}

int	print_core(t_command *cmd)
{
	t_list	*redir_list;
	t_redir	*redir;

	redir_list = cmd->redir_list;
	int i = 0;
	while (redir_list)
	{
		redir = (t_redir *)redir_list->content;
		printf("[%d] filename = %s\n",
				i,
				redir->to.filename);
				i++;
		redir_list = redir_list->next;
	}
	return (0);
}

int	print(t_ast *ast)
{
	cmd_loop(ast, print_core);
	return (0);
}
