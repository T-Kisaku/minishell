#include "expander.h"
#include "utils/ms_string.h"

int	word_split_handler(t_command *cmd);
static int	process_simple(t_list *head);
static int	count_words(char *str);

int	word_split_handler(t_command *cmd)
{
	if (cmd->type == CMD_SIMPLE)
	{
		if (process_simple(cmd->u.simple.token_list) != 0)
			return (1);
		cmd->u.simple.argc = ft_lstsize((t_list *)cmd->u.simple.token_list);
	}
	return (0);
}

int	process_simple(t_list *head)
{
	t_list	*cur;
	t_list	*prev;
	t_token_content *cur_token_content;
	char			*start;
	int				word_count;

	cur = head;
	while (cur)
	{
		cur_token_content = cur->content;
		if (cur_token_content->type == TOKEN_UNQUOTED_WORD)
		{
			word_count = count_words(cur_token_content->value);
			if (word_count > 1)
			{
				if (split_token(cur, word_count) != 0)
					return (1);
			}
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
static int	count_words(char *str)
{
	int	word_count;

	if (!str)
		return (-1);
	word_count = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
		{
			word_count++;
			while (*str && !ft_isspace(*str))
				str++;
		}
	}
	return (word_count);
}

