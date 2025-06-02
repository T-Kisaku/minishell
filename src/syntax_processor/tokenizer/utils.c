#include "tokenizer.h"

int		write_error(char *msg);
void	clean_tokens(t_token **head);
int		ft_isspace(int c);

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

void	clean_tokens(t_token **head)
{
	t_token	*cur_token;
	t_token	*next_token;

	if (!head || !*head) // 追加の安全性チェック
		return ;
	cur_token = *head;
	if (cur_token)
	{
		while (cur_token)
		{
			next_token = cur_token->next;
			if (cur_token->value)
				free(cur_token->value);
			free(cur_token);
			cur_token = next_token;
		}
		*head = NULL;
	}
}

//space is return (true(1));
int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}
