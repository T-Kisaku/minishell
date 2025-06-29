/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_content_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saueda <saueda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 10:09:43 by saueda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "minishell.h"
#include "utils/utils.h"
#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MSG "syntax error: here-doc in not intetractive mode is not supported"

static t_error	*init_heredoc_context(t_redir *redir, char **content,
					char **delimiter, size_t *delimiter_len);
static t_error	*read_line_loop(char **content, char *delimiter,
					size_t delimiter_len);
static bool		is_line_eof(char *line, char *delimiter, size_t delimiter_len);
static t_error	*append_line_to_content(char **content, char *line);

t_error	*input_heredoc_content_handler(t_redir *redir, t_minishell_state *shell)
{
	char	*content;
	char	*delimiter;
	size_t	delimiter_len;
	t_error	*error;

	(void)shell;
	error = NULL;
	if (redir->type != REDIR_HERE_DOC)
		return (error);
	if (shell->is_interactive != 0)
		return (new_error(EXIT_USER_ERR, MSG));
	error = init_heredoc_context(redir, &content, &delimiter, &delimiter_len);
	if (is_error(error))
		return (error);
	error = read_line_loop(&content, delimiter, delimiter_len);
	if (is_error(error))
	{
		free(content);
		return (error);
	}
	free(redir->redirect_source.filename_token->value);
	redir->redirect_source.filename_token->value = content;
	return (NULL);
}

static t_error	*init_heredoc_context(t_redir *redir, char **content,
		char **delimiter, size_t *delimiter_len)
{
	*content = ft_strdup("");
	if (!*content)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	*delimiter = redir->redirect_source.filename_token->value;
	*delimiter_len = ft_strlen(*delimiter);
	return (NULL);
}

static t_error	*read_line_loop(char **content, char *delimiter,
		size_t delimiter_len)
{
	char	*line;
	t_error	*append_result;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (new_error(EXIT_EOF, "exit"));
		if (!*line)
		{
			free(line);
			continue ;
		}
		if (is_line_eof(line, delimiter, delimiter_len))
			return (free_return_null((void**)&line));
		append_result = append_line_to_content(content, line);
		free(line);
		if (append_result)
			return (append_result);
	}
}

static bool	is_line_eof(char *line, char *delimiter, size_t delimiter_len)
{
	if (delimiter_len != ft_strlen(line))
		return (false);
	if (ft_strncmp(line, delimiter, delimiter_len) == 0)
		return (true);
	return (false);
}

static t_error	*append_line_to_content(char **content, char *line)
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
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERRO"));
	ft_memcpy(new_content, *content, content_len);
	ft_memcpy(new_content + content_len, line, line_len);
	new_content[new_content_len] = '\n';
	new_content[new_content_len + 1] = '\0';
	free(*content);
	*content = new_content;
	return (NULL);
}
