#include <stdio.h>
#include "tokenizer.h"

//現状libft.aを作成後に
//% cc -Wall -Wextra -Werror tokenizer_test.c tokenizer.c processes.c utils.c process_special_char.c -L../../libft -lft -o test_tokenizer
//とすれば実行ファイルを作成できます。

// トークンタイプを文字列に変換する関数
const char *token_type_to_string(e_token_type type) 
{
    switch (type) {
        case TOKEN_UNQUOTED_WORD: return "UNQUOTED_WORD";
        case TOKEN_SINGLE_QUOTED_WORD: return "SINGLE_QUOTED_WORD";
        case TOKEN_DOUBLE_QUOTED_WORD: return "DOUBLE_QUOTED_WORD";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_REDIR_INPUT: return "REDIR_INPUT";
        case TOKEN_REDIR_OUTPUT: return "REDIR_OUTPUT";
        case TOKEN_REDIR_HERE_DOC: return "REDIR_HERE_DOC";
        case TOKEN_REDIR_APPEND: return "REDIR_APPEND";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

// テスト用の出力関数
void print_tokens(t_token *tokens)
{
    t_token *current = tokens;
    int token_count = 0;
    
    printf("=== Tokenization Results ===\n");
    while (current)
    {
        printf("Token %d: '%s' -> %s\n", 
               ++token_count, 
               current->value, 
               token_type_to_string(current->type));
        current = current->next;
    }
    printf("Total tokens: %d\n\n", token_count);
}

// 個別テストケース
void test_case(const char *description, const char *input)
{
    printf("=== Test: %s ===\n", description);
    printf("Input: \"%s\"\n", input);
    
    t_token *tokens = tokenizer((char *)input);
    if (tokens)
    {
        print_tokens(tokens);
        clean_tokens(&tokens);
    }
    else
    {
        printf("Error: Tokenization failed\n\n");
    }
}

int main()
{
    printf("Minishell Tokenizer Test Suite\n");
    printf("==============================\n\n");
    
    // テストケース1: 基本的なコマンド
    test_case("Basic command", "echo hello world");
    
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
