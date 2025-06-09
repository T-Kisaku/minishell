#include "../../../libft/libft.h"
#include "../../../include/token.h"
#include "../../../include/tokenizer.h"
#include "../../../include/expander.h"
#include "../../../include/ast.h"
#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_token_list *create_token_node(e_token_type type, const char *value)
{
    t_token_list *node = malloc(sizeof(t_token_list));
    node->content = malloc(sizeof(t_token_content));
    node->content->type = type;
    node->content->value = strdup(value);
    node->next = NULL;
    return node;
}

void free_tokens(t_token_list *head)
{
    while (head)
    {
        t_token_list *tmp = head;
        head = head->next;
        free(tmp->content->value);
        free(tmp->content);
        free(tmp);
    }
}

void print_tokens(t_token_list *tokens)
{
    while (tokens)
    {
        printf("Type: %d, Value: %s\n", 
              tokens->content->type,
              tokens->content->value);
        tokens = tokens->next;
    }
}

// テストケース1: 基本的な変数展開
void test_basic_expansion()
{
    printf("\n=== 基本変数展開テスト ===\n");
    t_token_list *node = create_token_node(TOKEN_UNQUOTED_WORD, "$0");
    
    printf("Before:\n");
    print_tokens(node);
    
    expand_token_list(&node);
    
    printf("After:\n");
    print_tokens(node);
    free_tokens(node);
}

// テストケース2: クォートの扱い
void test_quote_handling()
{
    printf("\n=== クォート処理テスト ===\n");
    t_token_list *node1 = create_token_node(TOKEN_SINGLE_QUOTED_WORD, "$0");
    t_token_list *node2 = create_token_node(TOKEN_DOUBLE_QUOTED_WORD, "$0");
    node1->next = node2;

    printf("Before:\n");
    print_tokens(node1);
    
    expand_token_list(&node1);
    
    printf("After:\n");
    print_tokens(node1);
    free_tokens(node1);
}

// テストケース3: 複合トークン
void test_complex_expansion()
{
    printf("\n=== 複合展開テスト ===\n");
    t_token_list *head = create_token_node(TOKEN_UNQUOTED_WORD, "start$0");
    head->next = create_token_node(TOKEN_DOUBLE_QUOTED_WORD, "mid$#");
    head->next->next = create_token_node(TOKEN_UNQUOTED_WORD, "end$_");

    printf("Before:\n");
    print_tokens(head);
    
    expand_token_list(&head);
    
    printf("After:\n");
    print_tokens(head);
    free_tokens(head);
}

int main(void)
{
    test_basic_expansion();
    test_quote_handling();
    test_complex_expansion();
    return 0;
}
