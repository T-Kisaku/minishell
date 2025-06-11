#include  "ast_builder.h"
#include  "tokenizer/tokenizer.h"
#include <stdio.h>

//cc ast_builder_test.c simple_command.c ../tokenizer/process_special_char.c ../tokenizer/processes.c ../tokenizer/tokenizer.c .z./tokenizer/utils.c  ../../utils/is_space.c -L../../../libft -lft 

int main(void) {
    // 例: "ls -l /tmp" を手動でトークンリストにする
    t_list *tokens =  tokenizer("ls lss");
    t_list *cur = tokens;
    t_command *cmd = parse_simple_command(&cur);

    // 結果を表示
    for (int i = 0; i < cmd->u.simple.argc; i++)
        printf("argv[%d]: %s\n", i, cmd->u.simple.argv[i]);
    // メモリ解放も忘れずに
}
