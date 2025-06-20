
#include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(void)
{
	t_list			*tok1;
	t_list			*tok2;
	t_list			*tok3;
	t_token_content	*cont1;
	t_token_content	*cont2;
	t_token_content	*cont3;
	t_list *redir_list1;
	t_list *redir_list2;
	t_redir *redir1;
	t_redir *redir2;
	t_command		cmd;

	printf("test: %s\n", getenv("test"));
	// 1. トークンリスト作成: "echo" -> "hello" -> "world"
	tok1 = malloc(sizeof(t_list));
	tok2 = malloc(sizeof(t_list));
	tok3 = malloc(sizeof(t_list));
	cont1 = malloc(sizeof(t_token_content));
	cont2 = malloc(sizeof(t_token_content));
	cont3 = malloc(sizeof(t_token_content));
	cont1->value = ft_strdup(" >e'ch'o     abc<def");
	cont1->type = TOKEN_UNQUOTED_WORD;
	cont2->value = ft_strdup("zzz$abc$test");
	cont2->type = TOKEN_UNQUOTED_WORD;
	cont3->value = ft_strdup("w'o'r\"ld\"");
	cont3->type = TOKEN_UNQUOTED_WORD;
	tok1->content = cont1;
	tok1->next = tok2;
	tok2->content = cont2;
	tok2->next = tok3;
	tok3->content = cont3;
	tok3->next = NULL;
	// 2. コマンド構造体作成
	cmd.u.simple.token_list = tok1;
	cmd.u.simple.argc = 3;
	cmd.u.simple.argv = NULL;
	cmd.type = CMD_SIMPLE;
	redir_list1 = malloc(sizeof(t_list));
	redir_list2 = malloc(sizeof(t_list));
	cmd.redir_list= redir_list1;
	cmd.redir_list->next = redir_list2;
	redir1 = malloc(sizeof(t_redir));
	redir2 = malloc(sizeof(t_redir));
	redir1->type =REDIR_HERE_DOC;
	cmd.redir_list->content = redir1;
	cmd.redir_list->next->content = redir2;
	
	

	// 3. テスト対象関数呼び出し
	if (expand_handler(&cmd) != 0)
	{
		printf("error");
		return (1);
	}
	if (word_split_handler(&cmd) != 0)
	{
		printf("error");
		return (1);
	}
	if (quote_removal_handler(&cmd) != 0)
	{
		printf("error");
		return (1);
	}
	if (generate_argv_handler(&cmd) != 0)
	{
		printf("argv生成に失敗しました\n");
		free_token_list(&tok1);
		return (1);
	}
	// 4. 結果確認
	printf("%d\n", cmd.u.simple.argc);
	for (int i = 0; i < cmd.u.simple.argc; ++i)
	{
		printf("argv[%d]: %s\n", i, cmd.u.simple.argv[i]);
	}
	if (cmd.u.simple.argv[cmd.u.simple.argc] == NULL)
		printf("argvのNULL終端もOK\n");
	// 5. 後始末
	for (int i = 0; i < cmd.u.simple.argc; ++i)
		free(cmd.u.simple.argv[i]);
	free(cmd.u.simple.argv);
	free_token_list(&tok1);
	return (0);
}

// #include "expander.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // テスト用のヘルパー関数
// t_token_content *create_token_content(const char *value, t_token_type type) {
//     t_token_content *token = malloc(sizeof(t_token_content));
//     if (!token) return NULL;
//     token->value = ft_strdup(value);
//     token->type = type;
    // return token;
// }

// t_redir *create_test_redir(t_redir_type type, const char *filename_value, t_token_type token_type) {
//     t_redir *redir = new_redir();
//     if (!redir) return NULL;
    
//     redir->type = type;
//     redir->to.is_direct_to_fd = false;
//     redir->to.fd = -1;
//     redir->to.filename = NULL;
//     redir->to.filename_token = create_token_content(filename_value, token_type);
    
//     // fromは簡単のため設定しない（必要に応じて追加）
//     redir->from.is_direct_to_fd = true;
//     redir->from.fd = 1; // stdout
    
//     return redir;
// }

// void free_test_redir(t_redir *redir) {
//     if (!redir) return;
//     if (redir->to.filename) free(redir->to.filename);
//     if (redir->to.filename_token) {
//         if (redir->to.filename_token->value) free(redir->to.filename_token->value);
//         free(redir->to.filename_token);
//     }
//     free(redir);
// }

// int test_redir_expansion() {
//     printf("=== リダイレクションファイル名展開テスト ===\n");
    
//     // テストケース1: 通常のファイル名
//     t_redir *redir1 = create_test_redir(REDIR_OUTPUT, "output.txt", TOKEN_UNQUOTED_WORD);
//     if (!redir1) {
//         printf("テストケース1: メモリ確保失敗\n");
//         return 1;
//     }
    
//     printf("テストケース1 - 通常のファイル名:\n");
//     printf("  展開前: %s\n", redir1->to.filename_token->value);
    
//     if (expand_target(&redir1->to) != EXIT_SUCCESS) {
//         printf("  展開失敗\n");
//         free_test_redir(redir1);
//         return 1;
//     }
    
//     printf("  展開後: %s\n", redir1->to.filename);
//     printf("  結果: %s\n\n", strcmp(redir1->to.filename, "output.txt") == 0 ? "成功" : "失敗");
    
//     // テストケース2: 環境変数を含むファイル名
//     setenv("TESTFILE", "test_output", 1); // テスト用環境変数設定
//     t_redir *redir2 = create_test_redir(REDIR_OUTPUT, "$TESTFILE.log", TOKEN_UNQUOTED_WORD);
//     if (!redir2) {
//         printf("テストケース2: メモリ確保失敗\n");
//         free_test_redir(redir1);
//         return 1;
//     }
    
//     printf("テストケース2 - 環境変数を含むファイル名:\n");
//     printf("  展開前: %s\n", redir2->to.filename_token->value);
    
//     if (expand_target(&redir2->to) != EXIT_SUCCESS) {
//         printf("  展開失敗\n");
//         free_test_redir(redir1);
//         free_test_redir(redir2);
//         return 1;
//     }
    
//     printf("  展開後: %s\n", redir2->to.filename);
//     printf("  結果: %s\n\n", strstr(redir2->to.filename, "test_output") ? "成功" : "失敗");
    
//     // テストケース3: クォートされたファイル名
//     t_redir *redir3 = create_test_redir(REDIR_APPEND, "'quoted_file.txt'", TOKEN_SINGLE_QUOTED_WORD);
//     if (!redir3) {
//         printf("テストケース3: メモリ確保失敗\n");
//         free_test_redir(redir1);
//         free_test_redir(redir2);
//         return 1;
//     }
    
//     printf("テストケース3 - シングルクォートファイル名:\n");
//     printf("  展開前: %s\n", redir3->to.filename_token->value);
    
//     if (expand_target(&redir3->to) != EXIT_SUCCESS) {
//         printf("  展開失敗\n");
//         free_test_redir(redir1);
//         free_test_redir(redir2);
//         free_test_redir(redir3);
//         return 1;
//     }
    
//     printf("  展開後: %s\n", redir3->to.filename);
//     printf("  結果: %s\n\n", strcmp(redir3->to.filename, "'quoted_file.txt'") == 0 ? "成功" : "失敗");
    
//     // 後始末
//     free_test_redir(redir1);
//     free_test_redir(redir2);
//     free_test_redir(redir3);
//     unsetenv("TESTFILE");
    
//     return 0;
// }

// int test_command_with_redir() {
//     printf("=== コマンド+リダイレクション統合テスト ===\n");
    
//     // コマンド構造体作成
//     t_command cmd;
//     cmd.type = CMD_SIMPLE;
//     cmd.u.simple.token_list = NULL;
//     cmd.u.simple.argc = 0;
//     cmd.u.simple.argv = NULL;
    
//     // リダイレクションリスト作成
//     t_list *redir_list = NULL;
    
//     // リダイレクション1: > output.txt
//     t_redir *redir1 = create_test_redir(REDIR_OUTPUT, "output.txt", TOKEN_UNQUOTED_WORD);
//     t_list *redir_node1 = ft_lstnew(redir1);
//     ft_lstadd_back(&redir_list, redir_node1);
    
//     // リダイレクション2: >> $HOME/log.txt
//     setenv("HOME", "/tmp", 1);
//     t_redir *redir2 = create_test_redir(REDIR_APPEND, "$HOME/log.txt", TOKEN_UNQUOTED_WORD);
//     t_list *redir_node2 = ft_lstnew(redir2);
//     ft_lstadd_back(&redir_list, redir_node2);
    
//     cmd.redir_list = redir_list;
    
//     printf("リダイレクション展開前:\n");
//     t_list *current = redir_list;
//     int i = 1;
//     while (current) {
//         t_redir *redir = lstget_redir(current);
//         printf("  redir%d: %s\n", i++, redir->to.filename_token->value);
//         current = current->next;
//     }
    
//     // expand_handler呼び出し（リダイレクションファイル名展開）
//     if (expand_handler(&cmd) != 0) {
//         printf("expand_handler失敗\n");
//         // メモリ解放は省略（実際のコードでは必要）
//         return 1;
//     }
    
//     printf("\nリダイレクション展開後:\n");
//     current = redir_list;
//     i = 1;
//     while (current) {
//         t_redir *redir = lstget_redir(current);
//         printf("  redir%d: %s\n", i++, redir->to.filename ? redir->to.filename : "NULL");
//         current = current->next;
//     }
    
//     unsetenv("HOME");
//     // メモリ解放（実際のコードでは適切に行う）
    
//     return 0;
// }

// int main(void) {
//     printf("リダイレクション展開テスト開始\n\n");
    
//     if (test_redir_expansion() != 0) {
//         printf("リダイレクション展開テスト失敗\n");
//         return 1;
//     }
    
//     if (test_command_with_redir() != 0) {
//         printf("統合テスト失敗\n");
//         return 1;
//     }
    
//     printf("全テスト完了\n");
//     return 0;
// }
