
#include "../../../include/ast.h"
#include "../../../include/token.h"
#include "../../../libft/libft.h"
#include "../../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../../../include/expander.h"
int	expand_tokens_handler(t_command *cmd);
int		generate_argv_handler(t_command *cmd);
int		quote_removal_handler(t_command *cmd);
int		word_split_handler(t_command *cmd);
void	free_argv(char ***argv, int num);


// テスト用free関数
void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp;

	while (list)
	{
		tmp = list;
		free(list->content->value);
		free(list->content);
		list = list->next;
		free(tmp);
	}
}

int	main(void)
{
	t_token_list	*tok1;
	t_token_list	*tok2;
	t_token_list	*tok3;
	t_token_content	*cont1;
	t_token_content	*cont2;
	t_token_content	*cont3;
	t_command		cmd;
	printf("test: %s\n", getenv("test"));
	// 1. トークンリスト作成: "echo" -> "hello" -> "world"
	tok1 = malloc(sizeof(t_token_list));
	tok2 = malloc(sizeof(t_token_list));
	tok3 = malloc(sizeof(t_token_list));
	cont1 = malloc(sizeof(t_token_content));
	cont2 = malloc(sizeof(t_token_content));
	cont3 = malloc(sizeof(t_token_content));
	cont1->value = ft_strdup(" e'ch'o     abc def");
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
	// 3. テスト対象関数呼び出し
	if (expand_tokens_handler(&cmd) != 0)
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
		free_token_list(tok1);
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
	free_token_list(tok1);
	return (0);
}
