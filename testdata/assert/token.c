#include <assert.h>
#include <string.h>
#include "token.h"
#include "libft.h"

static void assert_single_token(t_token_content *expected, t_token_content *actual)
{
    assert(expected != NULL && actual != NULL);
    assert(expected->type == actual->type);
    assert(strcmp(expected->value, actual->value) == 0);
}

void assert_token_list(t_list *expected, t_list *actual)
{
    t_list *e_cur = expected;
    t_list *a_cur = actual;

    while (e_cur && a_cur)
    {
        t_token_content *e_token = (t_token_content *)e_cur->content;
        t_token_content *a_token = (t_token_content *)a_cur->content;
        assert_single_token(e_token, a_token);
        e_cur = e_cur->next;
        a_cur = a_cur->next;
    }
    assert(e_cur == NULL && a_cur == NULL);
}
