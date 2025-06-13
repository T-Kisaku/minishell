#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "token.h"
#include "libft.h"

static size_t list_size(t_list *lst) { return (size_t)ft_lstsize(lst); }

static void assert_single_token_equal(const t_token_content *et,
                                      const t_token_content *at,
                                      const char *path, size_t idx) {
  if (et->type != at->type || strcmp(et->value, at->value) != 0) {
    fprintf(stderr, "%s[%zu] token mismatch: exp(%d,'%s') act(%d,'%s')\n", path,
            idx, et->type, et->value, at->type, at->value);
    assert(0);
  }
}

void assert_token_list_equal(t_list *exp, t_list *act, const char *path) {
  size_t idx = 0;
  t_list *e = exp;
  t_list *a = act;
  while (e && a) {
    assert_single_token_equal(e->content, a->content, path, idx);
    idx++;
    e = e->next;
    a = a->next;
  }
  if (e || a) {
    fprintf(stderr, "%s size mismatch: exp=%zu act=%zu\n", path, list_size(exp),
            list_size(act));
    assert(0);
  }
}
