#include <stdio.h>
#include <stdlib.h>
#include "../../include/lexer.h"

// // トークンとセグメントを表示する関数
// void print_tokens(const t_token *head) {
//     int t = 0;
//     for (const t_token *tok = head; tok; tok = tok->next, t++) {
//         printf("token[%d]:\n", t);
//         int s = 0;
//         for (const t_segment *seg = tok->segments; seg; seg = seg->next, s++) {
//             const char *stype = "UNKNOWN";
//             if (seg->type == UNQUOTED_WORD) stype = "UNQUOTED";
//             else if (seg->type == SINGLE_QUOTED_WORD) stype = "SINGLE_QUOTED";
//             else if (seg->type == DOUBLE_QUOTED_WORD) stype = "DOUBLE_QUOTED";
//             printf("  segment[%d] (%s): \"%s\"\n", s, stype, seg->value ? seg->value : "(null)");
//         }
//     }
// }

// int main(void) {
//     const char *test_cases[] = {
//         "abc \"def ghi\" 'jkl' mno",
//         "\"\" ''",
// 		"\"",
//         "abc    def",
//         "'abc' \"def\" ghi",
//         "ajioefwaif\"fiowaf\"'oaklfeaw;'afweaf",
//         "\"abad\" aeafwe; 'afwfw'",
//         "",
// 		"abc<>d|<ad",
// 		"lw<<lwf<fiwef>jiwef>>iwef",
//         NULL // 終端
//     };

//     for (int i = 0; test_cases[i]; i++) {
//         t_token *head = NULL;
//         printf("==== Test case %d ====\n", i + 1);
//         printf("Input: [%s]\n", test_cases[i]);
//         // headはNULLで渡し、tokenize内で必要に応じて初期化・生成する設計に合わせる
//         if (tokenize(&head, (char *)test_cases[i]) != 0) {
//             printf("tokenize returned error\n");
//         } else if (head == NULL) {
//             printf("No tokens generated (empty input or error)\n");
//         } else {
//             print_tokens(head);
//         }
//         clean_tokens(&head);
//         printf("\n");
//     }
//     return 0;
// }

void print_tokens(const t_token *head) {
    int t = 0;
    for (const t_token *tok = head; tok; tok = tok->next, t++) {
        printf("token[%d]:\n", t);
        int s = 0;
        for (const t_segment *seg = tok->segments; seg; seg = seg->next, s++) {
            const char *stype = "UNKNOWN";
            if (seg->type == UNQUOTED_WORD) stype = "UNQUOTED";
            else if (seg->type == SINGLE_QUOTED_WORD) stype = "SINGLE_QUOTED";
            else if (seg->type == DOUBLE_QUOTED_WORD) stype = "DOUBLE_QUOTED";
            printf("  segment[%d] (%s): \"%s\"\n", s, stype, seg->value ? seg->value : "(null)");
        }
    }
}

// lexserの最終出力を表示する関数
void print_lexser_output(char **ary) {
    if (!ary) {
        printf("Lexser Output: NULL\n");
        return;
    }
    
    printf("Lexser Output:\n");
    for (int i = 0; ary[i]; i++) {
        printf("  [%d]: \"%s\"\n", i, ary[i]);
    }
}

// char**配列を解放する関数
void free_char_array(char **ary) {
    if (!ary)
        return;
    
    for (int i = 0; ary[i]; i++)
        free(ary[i]);
    free(ary);
}

// 比較テスト用の関数
void run_comparison_test(const char *input, int test_num) {
    printf("==== Test case %d ====\n", test_num);
    printf("Input: [%s]\n", input);
    
    // 1. tokenizeの詳細出力
    t_token *head = NULL;
    printf("\n--- Tokenize Details ---\n");
    if (tokenize(&head, (char *)input) != 0) {
        printf("tokenize returned error\n");
    } else if (head == NULL) {
        printf("No tokens generated (empty input or error)\n");
    } else {
        print_tokens(head);
    }
    
    // 2. lexserの最終出力
    printf("\n--- Final Lexser Output ---\n");
    char **result = lexser((char *)input);
    print_lexser_output(result);
    
    // メモリ解放
    clean_tokens(&head);
    free_char_array(result);
    printf("\n");
}

int main(void) {
    const char *test_cases[] = {
        "abc \"def ghi\" 'jkl' mno",
        "\"\" ''",
        "\"",
        "abc    def",
        "'abc' \"def\" ghi",
        "ajioefwaif\"fiowaf\"'oaklfeaw;'afweaf",
        "\"abad\" aeafwe; 'afwfw'",
        "",
        "abc<>d|<ad",
        "lw<<lwf<fiwef>jiwef>>iwef",
        // 追加のテストケース
        "echo \"hello world\" > file.txt",
        "'test'\"ing\"mixed",
        "cmd1; cmd2; cmd3",
        "echo 'special|chars;here' | grep test",
        NULL // 終端
    };

    printf("========================================\n");
    printf("    LEXER COMPREHENSIVE TEST\n");
    printf("========================================\n");

    for (int i = 0; test_cases[i]; i++) {
        run_comparison_test(test_cases[i], i + 1);
    }
    
    printf("========================================\n");
    printf("         ALL TESTS COMPLETED\n");
    printf("========================================\n");
    
    return 0;
}


