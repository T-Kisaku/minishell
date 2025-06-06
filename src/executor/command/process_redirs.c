#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ast.h"

static void process_redir_input(char *target);
static void process_redir_output(char *target);
static void process_redir_append(char *target);

void process_redirs(t_redir *redirs, int redir_count) {
  int redir_i;
  redir_i = 0;
  while (redir_i < redir_count && redirs != NULL) {
    if (redirs[redir_i].type == REDIR_INPUT)
      process_redir_input(redirs[redir_i].target);
    if (redirs[redir_i].type == REDIR_OUTPUT)
      process_redir_output(redirs[redir_i].target);
    // TODO: support append and heredoc
    if (redirs[redir_i].type == REDIR_APPEND)
      process_redir_append(redirs[redir_i].target);
    if (redirs[redir_i].type == REDIR_HERE_DOC) {
      exit(EXIT_FAILURE);
    }

    redir_i++;
  }
}

static void process_redir_input(char *target) {
  int input_fd;
  input_fd = open(target, O_RDONLY, 0444);
  dup2(input_fd, STDIN_FILENO);
  close(input_fd);
}

static void process_redir_output(char *target) {
  int output_fd;
  output_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  // TODO: add error handling
  dup2(output_fd, STDOUT_FILENO);
  close(output_fd);
}

static void process_redir_append(char *target) {
  int append_fd;
  append_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
  // TODO: add error handling
  dup2(append_fd, STDOUT_FILENO);
  close(append_fd);
}
