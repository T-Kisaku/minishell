#include "utils.h"

void	free_ast(t_ast *ast);
void	free_command_list(t_list **command_list);
void	free_command(t_command **cmd);
void	free_redir_list(t_list **head);

void	free_ast(t_ast *ast)
{
	t_and_or	*and_or;
	t_pipeline	*pipeline;

	if (!ast)
		return ;
	and_or = (t_and_or *)ast->content;
	if (and_or)
	{
		pipeline = and_or->pipeline;
		if (pipeline)
		{
			free_command_list(&pipeline->command_list);
			free(pipeline);
		}
		free(and_or);
	}
	free(ast);
}
void	free_command_list(t_list **command_list)
{
	t_list		*cur_cmd_list;
	t_list		*next;
	t_command	*cmd;

	if (!command_list || !*command_list)
		return ;
	cur_cmd_list = *command_list;
	while (cur_cmd_list)
	{
		cmd = (t_command *)cur_cmd_list->content;
		free_command(&cmd);
		next = cur_cmd_list->next;
		free(cur_cmd_list);
		cur_cmd_list = next;
	}
	*command_list = NULL;
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
		free_token_list((*cmd)->u.simple.token_list);
		free_argv((*cmd)->u.simple.argv, INT_MAX);
	}
	else if ((*cmd)->type == CMD_SUBSHELL)
	{
		;
	}
	free(*cmd);
	*cmd = NULL;
}

void	free_redir_list(t_list **head)
{
	t_list			*cur_redir;
	t_list			*next;
	t_redir_content	*redir_content;

	if (!head || !*head)
		return ;
	cur_redir = *head;
	while (cur_redir)
	{
		redir_content = (t_redir_content *)cur_redir->content;
		if (redir_content)
			free(redir_content->target);
		next = cur_redir->next;
		free(cur_redir);
		cur_redir = next;
	}
	*head = NULL;
}
