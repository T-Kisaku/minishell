#include "ast.h"
#include "testdata.h"
#include "token.h"
#include "syntax_processor/ast_builder.h"
t_testdata redir_mix(void){
  t_ast *ast_ptr = NULL;
  t_command *last_cmd = get_last_cmd(&ast_ptr);
  last_cmd->u.simple.argv = gen_argv("cat", NULL);
  last_cmd->u.simple.argc = gen_argc(last_cmd->u.simple.argv);
  last_cmd->u.simple.token_list = gen_token_list(1, TOKEN_UNQUOTED_WORD, "cat");
  t_list *last_redir_node;
  last_redir_node = lstadd_back_redir(&last_cmd->redir_list, REDIR_INPUT,
                        new_token("out.txt", TOKEN_UNQUOTED_WORD)
                                      );
  lstget_redir(last_redir_node)->redirect_source.filename =
      ft_strdup("out.txt");
  last_redir_node = lstadd_back_redir(&last_cmd->redir_list, REDIR_OUTPUT,
                        new_token("new.txt", TOKEN_UNQUOTED_WORD)
                                      );
  lstget_redir(last_redir_node)->redirect_source.filename =
      ft_strdup("new.txt");

  return (t_testdata){.input = "cat < out.txt > new.txt",
                      .token_list = gen_token_list(5,
                                                   TOKEN_UNQUOTED_WORD, "cat",
                                                   TOKEN_REDIR_INPUT, "<",
                                                   TOKEN_UNQUOTED_WORD, "out.txt",
                                                   TOKEN_REDIR_OUTPUT, ">",
                                                   TOKEN_UNQUOTED_WORD, "new.txt"
                                                   ),
                      .ast = ast_ptr,
                      .output_file = "new.txt"};
}




