#include "libft.h"
#include "token.h"
#include <stddef.h>

int			quote_remove_core(t_token *content);
static int	count_quotes(char *s);
static int	copy_without_quotes(char *dst, const char *src);

int	quote_remove_core(t_token *content)
{
	size_t	value_len;
	int		quote_count;
	char	*tmp;

	value_len = ft_strlen(content->value);
	quote_count = count_quotes(content->value);
	tmp = malloc(sizeof(char) * (value_len - quote_count + 1));
	if (!tmp)
		return (1);
	if (copy_without_quotes(tmp, content->value) != 0)
		return (1);
	free(content->value);
	content->value = tmp;
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
	if (!dst || !src)
		return (1);
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
