#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"

// exitコマンド（引数なし）
t_testdata exit_no_args(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit");

  return (t_testdata){.input = "minishell -c \"exit\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit"),
                      .ast = ast_ptr};
}

// exitコマンド（正常な数値引数）
t_testdata exit_with_number(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit 42", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 42");

  return (t_testdata){.input = "minishell -c \"exit 42\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 42"),
                      .ast = ast_ptr};
}

// exitコマンド（+プレフィックス付きの数値）
t_testdata exit_with_plus_prefix(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit +123", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +123");

  return (t_testdata){.input = "minishell -c \"exit +123\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +123"),
                      .ast = ast_ptr};
}

// exitコマンド（-プレフィックス付きの数値）
t_testdata exit_with_minus_prefix(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit -456", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit -456");

  return (t_testdata){.input = "minishell -c \"exit -456\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit -456"),
                      .ast = ast_ptr};
}

// exitコマンド（0の値）
t_testdata exit_with_zero(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit 0", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 0");

  return (t_testdata){.input = "minishell -c \"exit 0\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 0"),
                      .ast = ast_ptr};
}

// exitコマンド（複数の引数 - 最初の引数のみが使用される）
t_testdata exit_with_multiple_args(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit 42 extra args", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 42 extra args");

  return (t_testdata){.input = "minishell -c \"exit 42 extra args\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 42 extra args"),
                      .ast = ast_ptr};
}

// exitコマンド（不正な引数 - 数字以外の文字を含む）
t_testdata exit_with_invalid_arg(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit abc", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit abc");

  return (t_testdata){.input = "minishell -c \"exit abc\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit abc"),
                      .ast = ast_ptr};
}

// exitコマンド（+プレフィックス後に不正な文字）
t_testdata exit_with_plus_invalid(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit +abc", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +abc");

  return (t_testdata){.input = "minishell -c \"exit +abc\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +abc"),
                      .ast = ast_ptr};
}

// exitコマンド（-プレフィックス後に不正な文字）
t_testdata exit_with_minus_invalid(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit -xyz", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit -xyz");

  return (t_testdata){.input = "minishell -c \"exit -xyz\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit -xyz"),
                      .ast = ast_ptr};
}

// exitコマンド（大きな数値）
t_testdata exit_with_large_number(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit 255", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 255");

  return (t_testdata){.input = "minishell -c \"exit 255\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit 255"),
                      .ast = ast_ptr};
}

// exitコマンド（+プレフィックス付きの大きな数値）
t_testdata exit_with_plus_large_number(void) {
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("minishell", "-c", "exit +999", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +999");

  return (t_testdata){.input = "minishell -c \"exit +999\"",
                      .token_list = gen_token_list(3, TOKEN_UNQUOTED_WORD, "minishell", TOKEN_UNQUOTED_WORD, "-c", TOKEN_UNQUOTED_WORD, "exit +999"),
                      .ast = ast_ptr};
}
