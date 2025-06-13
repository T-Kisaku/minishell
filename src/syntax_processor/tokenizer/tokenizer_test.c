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

int main() {
  printf("Minishell Tokenizer Test Suite\n");
  printf("==============================\n\n");

  // テストケース1: 基本的なコマンド
  test_case("Basic command", "\"echo\" hello world");

  // テストケース2: シングルクォート
  test_case("Single quoted string", "echo 'hello world'");

  // テストケース3: ダブルクォート
  test_case("Double quoted string", "echo \"hello world\"");

  // テストケース4: パイプ
  test_case("Pipe command", "ls | grep test");

  // テストケース5: リダイレクション
  test_case("Output redirection", "echo hello > output.txt");

  // テストケース6: 入力リダイレクション
  test_case("Input redirection", "cat < input.txt");

  // テストケース7: Here-doc
  test_case("Here-doc", "cat << EOF");

  // テストケース8: Append redirection
  test_case("Append redirection", "echo hello >> output.txt");

  // テストケース9: 複合コマンド
  test_case("Complex command", "echo 'hello world' | cat > output.txt");

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
