#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"

static void process(t_redir_target *target, t_redir_type type) {
  int oflags;
  if (!target->is_direct_to_fd) {
    if (type == REDIR_INPUT)
      oflags = O_RDONLY;
	if (type == REDIR_HERE_DOC)
	  oflags = O_RDONLY; //heredoc用に追加
    if (type == REDIR_OUTPUT)
      oflags = O_WRONLY | O_CREAT | O_TRUNC;
    if (type == REDIR_APPEND)
      oflags = O_WRONLY | O_CREAT | O_APPEND;
    target->fd = open(target->filename, oflags, 0644);
	if(type == REDIR_HERE_DOC) //heredocの場合はOPENした直後にunlinkして削除する。
	{
		if(unlink(target->filename) == -1)
			//エラー処理
			;
	}
  }
  // TODO: error handling
  if (target->fd < 0)
    exit(1);
}

static void close_opened_fd(t_redir_target *target) {
  if (!target->is_direct_to_fd)
    close(target->fd);
}

// TODO: handle error for dup, open, close or any other funcitons related to fd
/*
 *  # Behaviour
 *  - get fd with filename
 *  - dup to STDIN or STDOUT
 *  - close opened fd with filename.
 *
 *  # Warn
 *  fd of pipe is not going to be cloesd automatically
 */
void process_redir_list(t_list *redir_list) {
  t_redir *redir;
  redir = NULL;
  while (redir_list) {
    redir = lstget_redir(redir_list);
    process(&redir->redirect_source, redir->type);
    process(&redir->to_be_redirected, redir->type);
    dup2(redir->redirect_source.fd, redir->to_be_redirected.fd);
    close_opened_fd(&redir->to_be_redirected);
    close_opened_fd(&redir->redirect_source);

    redir_list = redir_list->next;
  }
}
