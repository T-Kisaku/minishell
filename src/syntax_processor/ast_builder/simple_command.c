#include "ast_builder.h"

t_command *parse_simple_command(t_token_list **cur) {
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd) return NULL; // エラー処理
    cmd->type = CMD_SIMPLE;
    // 引数リストを作る
    int argc = 0;
    t_token_list *tmp = *cur;
    // 引数の数を数える
    while (tmp && tmp->content->type == TOKEN_UNQUOTED_WORD) {
        argc++;
        tmp = tmp->next;
    }
    // argv配列を作成
    cmd->u.simple.argv = malloc(sizeof(char*) * (argc + 1));
    cmd->u.simple.argc = argc;
    tmp = *cur;
    for (int i = 0; i < argc; i++) {
        cmd->u.simple.argv[i] = ft_strdup(tmp->content->value);
        tmp = tmp->next;
    }
    cmd->u.simple.argv[argc] = NULL;
    *cur = tmp; // トークン位置を進める
    return cmd;
}
