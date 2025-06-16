#include <stdlib.h>
#include "token.h"

// 削除用
void del(void *token_content) {
  t_token_content *tc;

  tc = (t_token_content *)token_content;
  if (!tc)
    return;
  free(tc->value);
  free(tc);
}

// 　t_token_content構造体作成用に作ったが、そもそもvalueの長さがわからないとmallocし直す必要があるから意味がない用に思う。
//  void	*create_token_content(void *content)
//  {
//  	t_token_content	*new_tc;

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
