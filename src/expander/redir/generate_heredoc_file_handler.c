#include "ast.h"
#include "libft.h"
#include "utils/utils.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define HEREDOC_TEMP_PREFIX "/tmp/.minishell_heredoc_"

int			generate_heredoc_file_handler(t_redir *redir);
static int	prepare_heredoc_file(t_redir *redir);
static int	generate_heredoc_filename(char *buffer, size_t buffer_size);
static int	create_and_write_heredoc(t_redir *redir);
//1時ファイル作成時にどこでエラーが発生しても問題なく関数外でファイルにアクセスできるようにできるだけ早くfilenameに代入する必要がある。

int	generate_heredoc_file_handler(t_redir *redir)
{
	char	*content;

	if (redir->type != REDIR_HERE_DOC)
		return (0);
	if (prepare_heredoc_file(redir) != 0)
		return (1);
	if (create_and_write_heredoc(redir) != 0)
		return (1);
	return (0);
}

static int	prepare_heredoc_file(t_redir *redir)
{
	char	temp_filename[256];

	if (generate_heredoc_filename(temp_filename, sizeof(temp_filename)) != 0)
		return (1);
	redir->to.filename = ft_strdup(temp_filename);
	if (!redir->to.filename)
		return (1);
	return 0;
}

static int	generate_heredoc_filename(char *buffer, size_t buffer_size)
{
	static int	counter = 0;
	char		*counter_str;
	char		*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (1);
	counter_str = ft_itoa(++counter);
	if (!counter_str)
	{
		free(pid_str);
		return (1);
	}
	ft_strlcpy(buffer, HEREDOC_TEMP_PREFIX, buffer_size);
	ft_strlcat(buffer, pid_str, buffer_size);
	ft_strlcat(buffer, "_", buffer_size);
	ft_strlcat(buffer, counter_str, buffer_size);
	free(pid_str);
	free(counter_str);
	return (0);
}

static int	create_and_write_heredoc(t_redir *redir)
{
	int		fd;
	char	*content;
	int write_result;

	fd = open(redir->to.filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (fd == -1)
	{
		free_and_null((void**)&redir->to.filename);
		return (1);
	}
	content = redir->to.filename_token->value;
	write_result = write(fd, content, ft_strlen(content));
	close(fd);
	if (write_result == -1)
	{
		if (unlink(redir->to.filename) == -1)
			; //適切な表示 perror?
		free_and_null((void**)&redir->to.filename);
		return (1);
	}
	return (0);
}
