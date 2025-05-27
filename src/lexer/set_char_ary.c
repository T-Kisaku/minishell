#include "../../include/lexer.h"


int	set_char_ary(t_token *head, char ***ary);
static void free_ary(char ***ary, int created_count);

int	set_char_ary(t_token *head, char ***ary)
{
	t_token		*cur_token;
	t_segment	*cur_seg;
	char		*token_str;
	char		*tmp;
	size_t		token_count;
	int i;	

	if (!head)
		return (write_error(""));
	cur_token = head;
	token_count = 0;
	while (cur_token)
	{
		token_count++;
		cur_token = cur_token->next;
	}
	*ary = malloc(sizeof(char *) * (token_count + 1));
	if (!*ary)
		return (write_error(""));
	cur_token = head;
	i = 0;
	while (cur_token)
	{
		token_str = ft_strdup("");
		if(!token_str)
		{
			free_ary(ary, i);
			return (write_error(""));
		}
		cur_seg = cur_token->segments;
		while (cur_seg)
		{
			tmp = ft_strjoin(token_str, cur_seg->value);
			free(token_str);
			if (!tmp)
			{
				free_ary(ary, i);
				return (write_error(""));
			}
			token_str = tmp;
			cur_seg = cur_seg->next;
		}
		(*ary)[i++] = token_str;
		cur_token = cur_token->next;
	}
	(*ary)[i] = NULL;
	return (0);
}


static void free_ary(char ***ary, int created_count)
{
	int i;

	i = 0;
	while(i < created_count)
	{
		free((*ary)[i]);
		i++;
	}
	free(*ary);
	*ary = NULL;
}
