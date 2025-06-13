// TODO: adapt to testdata
#include <stdio.h>
#include "tokenizer.h"
#include "utils/utils.h"
#include "testdata.h"

// 個別テストケース
void test_case(const char *description, const char *input) {
  printf("=== Test: %s ===\n", description);
  printf("Input: \"%s\"\n", input);

  t_list *token_list = tokenizer((char *)input);
  if (token_list) {
    print_token_list(token_list);
    free_token_list(&token_list);
  } else {
    printf("Error: Tokenization failed\n\n");
  }
}
void test(const char *description, t_testdata d) {
  printf("=== Test: %s ===\n", description);
  printf("Input: \"%s\"\n", d.input);
  t_list *actual = tokenizer((char *)d.input);
  assert_token_list_equal(&d.token_list, actual, "tokenizer");
  print_token_list(actual);
  free_token_list(&actual);
}

int main() {
  test("Basic command", echo_hello());
  test("Single quoted string", echo_no_expand_home());
  test("Double quoted string", echo_env_home());
  test("Pipe command", ls_pipe_grep());
  test("Output redirection", redir_output());
  test("Input redirection", redir_input());
  // TODO: adapt heredoc
  /* test_case("Here-doc", "cat << EOF"); */
  test("Append redirection", redir_append());
  test("Complex command", pipe_to_redir());
  return 0;
}
// TODO: WIP
int main_t() {
  printf("Minishell Tokenizer Test Suite\n");
  printf("==============================\n\n");

  // テストケース10: 複数のスペース
  test_case("Multiple spaces", "echo    hello     world");

  // テストケース11: 混合クォート
  test_case("Mixed quotes", "echo 'single' \"double\" unquoted");

  // テストケース12: 特殊文字の組み合わせ
  test_case("Special characters", "cmd < input.txt | filter >> output.txt");

  // テストケース13: 空文字列
  test_case("Empty quotes", "echo '' \"\"");

  // テストケース14: エラーケース（未閉じクォート）
  test_case("Unclosed quote (should fail)", "echo 'unclosed quote");

  printf("=== Test Suite Completed ===\n");
  return 0;
}
