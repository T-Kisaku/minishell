#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "testdata.h"

static size_t list_size(t_list *lst) { return (size_t)ft_lstsize(lst); }

static void assert_redir_target_equal(t_redir_target exp, t_redir_target act,
                                      const char *path) {
  if (exp.is_direct_to_fd != act.is_direct_to_fd) {
    fprintf(stderr, "%s.is_direct_to_fd exp=%d act=%d\n", path,
            exp.is_direct_to_fd, act.is_direct_to_fd);
    assert(0);
  }
  if (exp.fd != act.fd) {
    fprintf(stderr, "%s.fd exp=%d act=%d\n", path, exp.fd, act.fd);
    assert(0);
  }
  const char *e_name =
      exp.filename ? exp.filename
                   : (exp.filename_token ? exp.filename_token->value : NULL);
  const char *a_name =
      act.filename ? act.filename
                   : (act.filename_token ? act.filename_token->value : NULL);
  if ((e_name || a_name) &&
      (!e_name || !a_name || strcmp(e_name, a_name) != 0)) {
    fprintf(stderr, "%s.filename exp='%s' act='%s'\n", path,
            e_name ? e_name : "(null)", a_name ? a_name : "(null)");
    assert(0);
  }
}

static void assert_redir_equal(t_redir *exp, t_redir *act, const char *path) {
  if (exp->type != act->type) {
    fprintf(stderr, "%s.type exp=%d act=%d\n", path, exp->type, act->type);
    assert(0);
  }
  char buf[256];
  snprintf(buf, sizeof(buf), "%s.from", path);
  assert_redir_target_equal(exp->from, act->from, buf);
  snprintf(buf, sizeof(buf), "%s.to", path);
  assert_redir_target_equal(exp->to, act->to, buf);
}

static void assert_command_equal(t_command *exp, t_command *act,
                                 const char *path);

static void assert_pipeline_equal(t_pipeline *exp, t_pipeline *act,
                                  const char *path) {
  size_t idx = 0;
  t_list *e = exp->command_list;
  t_list *a = act->command_list;
  while (e && a) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%s.command[%zu]", path, idx);
    assert_command_equal(lstget_command(e), lstget_command(a), buf);
    e = e->next;
    a = a->next;
    idx++;
  }
  if (e || a) {
    fprintf(stderr, "%s command count mismatch exp=%zu act=%zu\n", path,
            list_size(exp->command_list), list_size(act->command_list));
    assert(0);
  }
}

static void assert_and_or_equal(t_and_or *exp, t_and_or *act,
                                const char *path) {
  if (exp->op_next != act->op_next) {
    fprintf(stderr, "%s.op_next exp=%d act=%d\n", path, exp->op_next,
            act->op_next);
    assert(0);
  }
  char buf[256];
  snprintf(buf, sizeof(buf), "%s.pipeline", path);
  assert_pipeline_equal(exp->pipeline, act->pipeline, buf);
}

static void assert_ast_node_equal(t_ast *exp, t_ast *act, const char *path) {
  size_t idx = 0;
  while (exp && act) {
    char buf[256];
    snprintf(buf, sizeof(buf), "%s[%zu]", path, idx);
    assert_and_or_equal(lstget_and_or(exp), lstget_and_or(act), buf);
    exp = exp->next;
    act = act->next;
    idx++;
  }
  if (exp || act) {
    fprintf(stderr, "%s size mismatch exp=%zu act=%zu\n", path, list_size(exp),
            list_size(act));
    assert(0);
  }
}

static void assert_simple_command_equal(u_command *exp, u_command *act,
                                        const char *path) {
  if (exp->simple.argc != act->simple.argc) {
    fprintf(stderr, "%s.argc exp=%d act=%d\n", path, exp->simple.argc,
            act->simple.argc);
    assert(0);
  }
  for (int i = 0; i < exp->simple.argc; i++) {
    const char *e_arg = exp->simple.argv ? exp->simple.argv[i] : NULL;
    const char *a_arg = act->simple.argv ? act->simple.argv[i] : NULL;
    if ((e_arg || a_arg) && (!e_arg || !a_arg || strcmp(e_arg, a_arg) != 0)) {
      fprintf(stderr, "%s.argv[%d] exp='%s' act='%s'\n", path, i,
              e_arg ? e_arg : "(null)", a_arg ? a_arg : "(null)");
      assert(0);
    }
  }
// TODO: adapt testdata eg) add propper data to u.simple.token_list 
//   char buf[256];
//   snprintf(buf, sizeof(buf), "%s.token", path);
//   if (exp->simple.token_list || act->simple.token_list)
//     assert_token_list_equal(exp->simple.token_list, act->simple.token_list,
//                             buf);
}

static void assert_command_equal(t_command *exp, t_command *act,
                                 const char *path) {
  if (exp->type != act->type) {
    fprintf(stderr, "%s.type exp=%d act=%d\n", path, exp->type, act->type);
    assert(0);
  }

  char buf[256];
  if (exp->redir_list || act->redir_list) {
    size_t idx = 0;
    t_list *e = exp->redir_list;
    t_list *a = act->redir_list;
    while (e && a) {
      snprintf(buf, sizeof(buf), "%s.redir[%zu]", path, idx);
      assert_redir_equal(lstget_redir(e), lstget_redir(a), buf);
      e = e->next;
      a = a->next;
      idx++;
    }
    if (e || a) {
      fprintf(stderr, "%s.redir count mismatch exp=%zu act=%zu\n", path,
              list_size(exp->redir_list), list_size(act->redir_list));
      assert(0);
    }
  }

  if (exp->type == CMD_SIMPLE) {
    snprintf(buf, sizeof(buf), "%s.simple", path);
    assert_simple_command_equal(&exp->u, &act->u, buf);
  } else if (exp->type == CMD_SUBSHELL) {
    snprintf(buf, sizeof(buf), "%s.subshell", path);
    assert_ast_node_equal(exp->u.subshell.and_or_list,
                          act->u.subshell.and_or_list, buf);
  }
}

void assert_ast_equal(t_ast *expected, t_ast *actual) {
  assert_ast_node_equal(expected, actual, "ast");
}
