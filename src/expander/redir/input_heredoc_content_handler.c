#include "ast.h"
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int			input_heredoc_content_handler(t_redir *redir);
static int	init_heredoc_context(t_redir *redir, char **content,
				char **delimiter, size_t *delimiter_len);
static int	read_line_loop(char **content, char *delimiter,
				size_t delimiter_len);
static bool	is_line_EOF(char *line, char *delimiter, size_t delimiter_len);
static int	append_line_to_content(char **content, char *line);

int	input_heredoc_content_handler(t_redir *redir)
{
	char	*content;
	char	*delimiter;
	size_t	delimiter_len;

	if (redir->type != REDIR_HERE_DOC)
		return (0);
	if (init_heredoc_context(redir, &content, &delimiter, &delimiter_len) != 0)
		return (1);
	if (read_line_loop(&content, delimiter, delimiter_len) != 0)
	{
		free(content);
		return (1);
	}
	free(redir->to.filename_token->value);
	redir->to.filename_token->value = content;
	return (0);
}

static int	init_heredoc_context(t_redir *redir, char **content,
		char **delimiter, size_t *delimiter_len)
{
	*content = ft_strdup("");
	if (!*content)
		return (1);
	*delimiter = redir->to.filename_token->value;
	*delimiter_len = ft_strlen(*delimiter);
	return (0);
}

static int	read_line_loop(char **content, char *delimiter,
		size_t delimiter_len)
{
	char	*line;
	int		append_result;

	while (1)
	{
		line = readline("> ");
		if (!line) //EOF(Ctrl + D)
		{
			//出力
			return (0);
		}
		if (is_line_EOF(line, delimiter, delimiter_len))
		{
			free(line);
			return (0);
		}
		append_result = append_line_to_content(content, line);
		free(line);
		if (append_result != 0)
			return (1);
	}
}

static bool	is_line_EOF(char *line, char *delimiter, size_t delimiter_len)
{
	if (delimiter_len != ft_strlen(line))
		return (false);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0)
		return (true);
	return (false);
}

static int	append_line_to_content(char **content, char *line)
{
	char	*new_content;
	size_t	content_len;
	size_t	line_len;
	size_t	new_content_len;

	content_len = ft_strlen(*content);
	line_len = ft_strlen(line);
	new_content_len = content_len + line_len;
	new_content = malloc(sizeof(char) * (content_len + line_len + 2));
	if (!new_content)
		return (1);
	ft_memcpy(new_content, *content, content_len);
	ft_memcpy(new_content + content_len, line, line_len);
	new_content[new_content_len] = '\n';
	new_content[new_content_len + 1] = '\0';
	free(*content);
	*content = new_content;
	return (0);
}
