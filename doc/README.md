## テスト

### やり方

```bash
make test
# or
make test_lexer_test
```

### 書き方

1. `なんでもよい`+`_test.c`を同じフォルダー内に置く。
1. `asert.h`と`テストしたい関数のプロタイプ宣言が入ってるヘッダ`を読み込む

#### 例

`src/lexer/lexer.c`をテストしたい場合は`src/lexer/lexer_test.c`を作る。`src/lexer_test.c`でも良い

```c
// 中身
#include <assert.h>
#include <minishell.h>
#include <string.h>
int main() {
  char execute_str[] = "echo fire";
  char **tokens = lexer(execute_str);
  assert(strcmp(tokens[0], "echo"));
  assert(strcmp(tokens[1], "fire"));
  return (0);
}
`
```


valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp minishell
これでreadline関連の我々ではどうしようもないメモリリークを除外できる。