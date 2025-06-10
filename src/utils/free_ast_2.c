#include "ast.h"

void	free_token_list(t_list **head);
void	free_argv(char ***argv, int num);


void	free_token_list(t_list **head)
{
	t_list			*cur_token;
	t_list			*next_token;
	t_token_content	*cur_token_content;

	if (!head || !*head)
		return ;
	cur_token = *head;
	while (cur_token)
	{
		cur_token_content = (t_token_content*)cur_token->content;
		if (cur_token_content)
		{
			free(cur_token_content->value);
			free(cur_token_content);
		}
		next_token = cur_token->next;
		free(cur_token);
		cur_token = next_token;
	}
	*head = NULL;
}

void	free_argv(char ***argv, int num)
{
	int	i;

	if (!argv || !*argv)
		return ;
	i = 0;
	if (num == INT_MAX)
		while ((*argv)[i])
		{
			free((*argv)[i]);
			(*argv)[i] = NULL;
			i++;
		}
	else
	{
		while (i < num)
		{
			free((*argv)[i]);
			(*argv)[i] = NULL;
			i++;
		}
	}
	free(*argv);
	*argv = NULL;
}