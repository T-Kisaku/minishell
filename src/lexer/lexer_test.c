#include <stdio.h>
#include <stdlib.h>
#include "../../include/lexer.h"


// トークンとセグメントを表示する関数
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
            printf("  segment[%d] (%s): \"%s\"\n", s, stype, seg->value);
        }
    }
}

int main(void) {
    const char *test_cases[] = {
        "abc \"def ghi\" 'jkl' mno",
        "\"\" ''",
        "abc    def",
        "'abc' \"def\" ghi",
        "ajioefwaif\"fiowaf\"'oaklfeaw;'afweaf",
        "\"abad\" aeafwe; 'afwfw'",
        "",
        NULL // 終端
    };
    for (int i = 0; test_cases[i]; i++) {
        t_token *head;
		head = malloc(sizeof(t_token));
        head->segments = NULL;
        head->next = NULL;
        printf("==== Test case %d ====\n", i+1);
        printf("Input: [%s]\n", test_cases[i]);
        if (set_tokens(head, (char *)test_cases[i]) != 0) {
            printf("set_tokens returned error\n");
        } else {
            print_tokens(head);
        }
        clean_tokens(&head);
        printf("\n");
    }
    return 0;
}

