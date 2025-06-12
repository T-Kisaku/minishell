#include <stdlib.h> //free,
#include "libft.h" //ft_lstclear
#include "ast.h"
#include "token.h"
#include "utils.h"

// #include "libft.h" // TODO: adapt libft's ft_lstclear,
//	just make del function for each struct!!

void	free_ast(t_ast **ast);
void	del_and_or(void *content);
void	free_command_list(t_list **command_list);
void	del_command(void *content);
void	free_command(t_command **cmd);

void	free_ast(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	ft_lstclear(ast, del_and_or);	
	*ast = NULL;
}


void	del_and_or(void *content)
{
	t_and_or	*and_or;

	if (!content)
		return ;
	and_or = (t_and_or *)content;
	free_command_list(&and_or->pipeline->command_list);
	free_(and_or->pipeline);
	free(and_or);
}
void	free_command_list(t_list **command_list)
{
	if (!command_list || !*command_list)
		return ;
	ft_lstclear(command_list, del_command);
}

void	del_command(void *content)
{
	t_command	*cmd;

	if (!content)
		return ;
	cmd = (t_command *)content;
	free_command(&cmd);
}

void	free_command(t_command **cmd)
{
	t_list			*cur_token;
	t_list			*next;
	t_token_content	*token_content;

	if (!cmd || !*cmd)
		return ;
	free_redir_list(&(*cmd)->redir_list);
	if ((*cmd)->type == CMD_SIMPLE)
	{
		free_token_list(&(*cmd)->u.simple.token_list);
		free_argv(&(*cmd)->u.simple.argv, INT_MAX);
	}
	else if ((*cmd)->type == CMD_SUBSHELL)
	{
		;
	}
	free(*cmd);
	*cmd = NULL;
}
