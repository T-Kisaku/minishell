#include "../../include/token.h"
#include "../../libft/libft.h"

// void				ft_lstclear(t_list **lst, void (*del)(void *));
// void				ft_lstiter(t_list *lst, void (*f)(void *));
// t_list				*ft_lstmap(t_list *lst, void *(*f)(void
// *),

// 削除用
void	del(void *token_content)
{
	t_token_content	*tc;

	tc = (t_token_content *)token_content;
	if (!tc)
		return ;
	free(tc->value);
	free(tc);
}

//　t_token_content構造体作成用に作ったが、そもそもvalueの長さがわからないとmallocし直す必要があるから意味がない用に思う。
// void	*create_token_content(void *content)
// {
// 	t_token_content	*new_tc;

// 	(void)content;
// 	new_tc = malloc(sizeof(t_token_content));
// 	if (!new_tc)
// 		return (NULL);
// 	new_tc->value = malloc(sizeof(char*));
// 	if( !new_tc->value)
// 	{
// 		free(new_tc);
// 		return NULL;
// 	}
// 	return (new_tc);
// }

// 繰り返し処理用

// 新たな連結リストを作る用の関数が必要！(map関数を調べればよき！！)

// #include "libft.h"
// #include "token.h"
// #include <unistd.h>

// int main() {
// int *i = malloc(sizeof(int));

// t_token_list *lst = (t_token_list *)ft_lstnew(i);

// }
