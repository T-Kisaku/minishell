#include "ast_builder.h"

t_command	*parse_simple_command(t_list **cur)
{
	t_token_content	*token_content;
	t_command		*cmd;
	int				argc;
	t_list			*tmp;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL); // エラー処理
	cmd->type = CMD_SIMPLE;
	// 引数リストを作る
	argc = 0;
	tmp = *cur;
	// 引数の数を数える
	token_content = (t_token_content *)tmp->content;
	while (tmp && token_content->type == TOKEN_UNQUOTED_WORD)
	{
		argc++;
		tmp = tmp->next;
		token_content = (t_token_content *)tmp->content;
	}
	// argv配列を作成
	cmd->u.simple.argv = malloc(sizeof(char *) * (argc + 1));
	cmd->u.simple.argc = argc;
	tmp = *cur;
	for (int i = 0; i < argc; i++)
	{
		token_content = (t_token_content *)tmp->content;
		cmd->u.simple.argv[i] = ft_strdup(token_content->value);
		tmp = tmp->next;
	}
	cmd->u.simple.argv[argc] = NULL;
	*cur = tmp; // トークン位置を進める
	return (cmd);
}
