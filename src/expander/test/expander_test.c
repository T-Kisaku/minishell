#include <stdio.h>
#include "ast.h"
#include "error.h"
#include "token.h"
#include "utils/utils.h"
#include "minishell.h"
#include "testdata.h"
#include "syntax_processor.h"

int testcase(char *s);
t_error *print_cmd(t_command *cmd);
t_error *print_redir(t_command *cmd);
t_error *print(t_ast *ast);

int main(void) {
  /* testcase("cat $abc <<&abc bbb > aaa.txt"); */
  testcase("echo $SHELL");
  return (0);
}

int testcase(char *s) {
  t_ast *ast;
  t_list *list;

  check_error(str_to_token(s, &list));
  check_error(token_to_ast(list, &ast));
  check_error(expand_ast(ast));
  print(ast);
  free_ast(&ast);
  return (0);
}

t_error *print_cmd(t_command *cmd) {
  t_list *cmd_list;
  t_token *content;
  int i;

  cmd_list = cmd->u.simple.token_list;
  i = 0;
  while (cmd_list) {
    content = (t_token *)cmd_list->content;
    printf("[%d] cmd_name = %s\n", i, content->value);
    i++;
    cmd_list = cmd_list->next;
  }
  return NULL;
}

t_error *print_redir(t_command *cmd) {
  t_list *redir_list;
  t_redir *redir;
  int i;

  redir_list = cmd->redir_list;
  i = 0;
  while (redir_list) {
    redir = (t_redir *)redir_list->content;
    printf("[%d] filename = %s\n", i, redir->redirect_source.filename);
    i++;
    redir_list = redir_list->next;
  }
  return (NULL);
}

t_error *print(t_ast *ast) {
  cmd_loop(ast, print_redir);
  cmd_loop(ast, print_cmd);
  return (NULL);
}
