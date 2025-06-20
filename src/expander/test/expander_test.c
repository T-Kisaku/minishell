#include "ast.h"
#include "expander.h"
#include "syntax_processor.h"
#include "token.h"
#include "utils/utils.h"
#include <stdio.h>

int	testcase(char *s);
int	print_cmd(t_command *cmd);
int	print_redir(t_command *cmd);
int	print(t_ast *ast);

int	main(void)
{
	testcase("cat $abc <<&abc bbb > aaa.txt");
	return (0);
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

int	print_cmd(t_command *cmd)
{
	t_list			*cmd_list;
	t_token_content	*content;
	int				i;

	cmd_list = cmd->u.simple.token_list;
	i = 0;
	while (cmd_list)
	{
		content = (t_token_content *)cmd_list->content;
		printf("[%d] cmd_name = %s\n",
				i,
				content->value);
		i++;
		cmd_list = cmd_list->next;
	}
	return (0);
}

int	print_redir(t_command *cmd)
{
	t_list	*redir_list;
	t_redir	*redir;
	int		i;

	redir_list = cmd->redir_list;
	i = 0;
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
	cmd_loop(ast, print_redir);
	cmd_loop(ast, print_cmd);
	return (0);
}
