#include "check_syntax.h"
#include "minishell.h"
#include "syntax_processor.h"
#include "token.h"
#include <stdio.h>
#include <syntax_processor.h>
#include "error.h"
int check(char *s, t_minishell_state *shell);

int main(void) {
  /* check("hello \'\nnworld\n \'", shell); */
  // check("|");
  // check("<");
  return (0);
}

int check(char *s, t_minishell_state *shell) {
  t_list *list;
  t_error *error;
  t_ast *ast;
  list = NULL;
  ast = NULL;
  error = str_to_token(s, &list);
  if (error) {
    printf("tokenizer_error\n");
    return (1);
  }
  error = check_syntax(list, shell);
  if (error) {
    printf("check_syntax_error\n");
    return (1);
  }
  error = token_to_ast(list, &ast);
  if (error) {
    printf("token_to_ast_error\n");
    return (1);
  }
  printf("OK\n");
  return (0);
}
