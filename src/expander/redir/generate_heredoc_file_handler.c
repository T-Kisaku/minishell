/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_heredoc_file_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkisaku <tkisaku@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 08:52:58 by tkisaku           #+#    #+#             */
/*   Updated: 2025/06/29 08:52:58 by tkisaku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "exit_status.h"
#include "libft.h"
#include "minishell.h"
#include "utils/utils.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define HEREDOC_TEMP_PREFIX "/tmp/.minishell_heredoc_"

t_error			*generate_heredoc_file_handler(t_redir *redir,
					t_minishell_state *shell);
static t_error	*prepare_heredoc_file(t_redir *redir);
static t_error	*generate_heredoc_filename(char *buffer, size_t buffer_size);
static t_error	*create_and_write_heredoc(t_redir *redir);
// 1時ファイル作成時にどこでエラーが発生しても問題なく関数外でファイルにアクセスできるようにできるだけ早くfilenameに代入する必要がある。

t_error	*generate_heredoc_file_handler(t_redir *redir, t_minishell_state *shell)
{
	t_error	*error;

	(void)shell; // shellは使用されていないため、警
	error = NULL;
	if (redir->type != REDIR_HERE_DOC)
		return (error);
	error = prepare_heredoc_file(redir);
	if (is_error(error))
		return (error);
	error = create_and_write_heredoc(redir);
	return (error);
}

static t_error	*prepare_heredoc_file(t_redir *redir)
{
	char	temp_filename[256];
	t_error	*error;

	error = generate_heredoc_filename(temp_filename, sizeof(temp_filename));
	if (is_error(error))
		return (error);
	redir->redirect_source.filename = ft_strdup(temp_filename);
	if (!redir->redirect_source.filename)
		return (new_error(EXIT_INTERNAL_ERR, "MALLOC ERROR"));
	return (error);
}

static t_error	*generate_heredoc_filename(char *buffer, size_t buffer_size)
{
	static int	counter = 0;
	char		*counter_str;
	char		*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (new_error(EXIT_INTERNAL_ERR, "itoa ERRO"));
	counter_str = ft_itoa(++counter);
	if (!counter_str)
	{
		free(pid_str);
		return (new_error(EXIT_INTERNAL_ERR, "itoa ERRO"));
	}
	ft_strlcpy(buffer, HEREDOC_TEMP_PREFIX, buffer_size);
	ft_strlcat(buffer, pid_str, buffer_size);
	ft_strlcat(buffer, "_", buffer_size);
	ft_strlcat(buffer, counter_str, buffer_size);
	free(pid_str);
	free(counter_str);
	return (NULL);
}

static t_error	*create_and_write_heredoc(t_redir *redir)
{
	int		fd;
	char	*content;
	int		write_result;

	fd = open(redir->redirect_source.filename, O_WRONLY | O_CREAT | O_EXCL,
			0600);
	if (fd == -1)
	{
		free_and_null((void **)&redir->redirect_source.filename);
		return (new_error(EXIT_INTERNAL_ERR, "OPEN ERRO"));
	}
	content = redir->redirect_source.filename_token->value;
	write_result = write(fd, content, ft_strlen(content));
	close(fd);
	if (write_result == -1)
	{
		// 適切な表示 perror?
		if (unlink(redir->redirect_source.filename) == -1)
		{
		}
		free_and_null((void **)&redir->redirect_source.filename);
		return (new_error(EXIT_INTERNAL_ERR, "WRITE ERRO"));
	}
	return (NULL);
}
