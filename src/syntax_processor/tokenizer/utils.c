#include "tokenizer.h"

int		write_error(char *msg);
void	clean_token_list(t_list **head);

//always return (1);
int	write_error(char *msg)
{
	char	*prefix;

	prefix = "minishell: ";
	write(2, prefix, ft_strlen(prefix));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void	clean_token_list(t_list **head)
{
	t_list	*cur_token;
	t_list	*next_token;
	t_token_content *cur_token_content;

	if (!head || !*head) // 追加の安全性チェック
		return ;
	cur_token = *head;
	while (cur_token)
	{
		next_token = cur_token->next;
		cur_token_content = cur_token->content;
		if (cur_token->content)
		{
			free(cur_token_content->value);
			free(cur_token_content);
		}
		free(cur_token);
		cur_token = next_token;
	}
	*head = NULL;
}
