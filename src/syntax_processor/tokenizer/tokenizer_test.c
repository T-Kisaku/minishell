#include <stdio.h>
#include "syntax_processor.h"

#include "testdata.h"

void test(const char *description, t_testdata d) {
  printf("=== Test: %s ===\n", description);
  printf("Input: \"%s\"\n", d.input);
  t_list *actual;
  actual = NULL;
  str_to_token(d.input, &actual);
  print_token_list(actual);
  assert_token_list_equal(d.token_list, actual, "tokenizer");
  lstclear_token(&actual);
  free_testdata(&d);
}

int main() {
  test("Basic command", echo_simple_string());
  /* test("Single quoted string", echo_no_expand_home()); */
  /* test("Double quoted string", echo_env_home()); */
  test("Pipe command", ls_pipe_grep());
  test("Output redirection", redir_output());
  test("Output redirection without space", redir_output_nospace());
  test("Input redirection", redir_input());
  // TODO: adapt heredoc
  /* test_case("Here-doc", "cat << EOF"); */
  test("Append redirection", redir_append());
  return 0;
}
