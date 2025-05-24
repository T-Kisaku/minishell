#include "../../include/lexer.h"

int	write_error(char *msg);
int syntax_error(const char *token, size_t len);
void	clean_tokens(t_token **head);
int	ft_isspace(int c);

//always return 1;
int	write_error(char *msg)
{
	char	*prefix;

	prefix = "minishell: ";
	write(2, prefix, ft_strlen(prefix));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}


//always return 1;
int syntax_error(const char *token, size_t len)
{
	const char	*prefix;
	const char	*suffix;

	prefix = "minishell: syntax error near unexpected token `";
	suffix = "'\n";
	write(2, prefix, ft_strlen(prefix));
	write(2, token, len);
	write(2, suffix, ft_strlen(suffix));
	return (1);
}

void	clean_tokens(t_token **head)
{
	t_token		*cur_token;
	t_token		*next_token;
	t_segment	*cur_seg;
	t_segment	*next_seg;

	cur_token = *head;
	if (cur_token)
	{
		while (cur_token)
		{
			cur_seg = cur_token->segments;
			while (cur_seg)
			{
				free(cur_seg->value);
				next_seg = cur_seg->next;
				free(cur_seg);
				cur_seg = next_seg;
			}
			next_token = cur_token->next;
			free(cur_token);
			cur_token = next_token;
		}
		*head = NULL;
	}
}

//space is return true(1);
int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}
