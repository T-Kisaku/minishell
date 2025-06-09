#include "../../../libft/libft.h"
#include "../../../include/ast.h"
#include "../../../include/token.h"

int			quote_removal_handler(t_command *cmd);
static int	process_simple(t_token_list *head);
static int	count_quotes(char *s);
static int	copy_without_quotes(char *dst, const char *src);

int	quote_removal_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (process_simple(cmd->u.simple.token_list) != 0)
			return (1);
	}
	return (0);
}

static int	process_simple(t_token_list *head)
{
	t_token_list	*cur;
	size_t			value_len;
	int				quote_count;
	char			*tmp;

	cur = head;
	while (cur)
	{
		value_len = ft_strlen(cur->content->value);
		quote_count = count_quotes(cur->content->value);
		tmp = malloc(sizeof(char) * (value_len - quote_count + 1));
		if (!tmp)
			return (1);
		if (copy_without_quotes(tmp, cur->content->value) != 0)
			return (1);
		free(cur->content->value);
		cur->content->value = tmp;
		cur = cur->next;
	}
	return (0);
}

static int	count_quotes(char *s)
{
	int	quote_count;

	if (!s)
		return (-1);
	quote_count = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			quote_count++;
		s++;
	}
	return (quote_count);
}

static int	copy_without_quotes(char *dst, const char *src)
{
	int	index;

	if (!dst || !src)
		return (1);
	index = 0;
	while (*src)
	{
		if (*src != '\'' && *src != '"')
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	return (0);
}
