SRCS = \
src/utils/ast/and_or/del.c \
src/utils/ast/and_or/new.c \
src/utils/ast/and_or/other.c \
src/utils/ast/command/del.c \
src/utils/ast/command/new.c \
src/utils/ast/command/other.c \
src/utils/ast/pipeline/del.c \
src/utils/ast/pipeline/new.c \
src/utils/ast/redirection/del.c \
src/utils/ast/redirection/new.c \
src/utils/ast/redirection/other.c \
src/utils/ast/cmd_loop.c \
src/utils/ast/redir_loop.c \
src/utils/free_and_null.c \
src/utils/write_error.c \
src/utils/argv.c \
src/utils/ms_string.c \
src/utils/token/copy.c \
src/utils/token/del.c \
src/utils/token/new.c \
src/utils/token/get.c \
src/syntax_processor/ast_builder/token_to_ast.c \
src/syntax_processor/ast_builder/processes.c \
src/syntax_processor/ast_builder/utils.c \
src/syntax_processor/tokenizer/str_to_token.c \
src/syntax_processor/tokenizer/token_extraction.c \
src/syntax_processor/tokenizer/tokenize_loop.c \
src/syntax_processor/tokenizer/process_special_char.c \
src/syntax_processor/check_syntax/check_syntax.c \
src/syntax_processor/str_to_ast.c \
src/executor/command/builtin/cd.c \
src/executor/command/builtin/echo.c \
src/executor/command/builtin/env.c \
src/executor/command/builtin/exit.c \
src/executor/command/builtin/export.c \
src/executor/command/builtin/unset.c \
src/executor/command/builtin/exec_builtin_cmd.c \
src/executor/command/builtin/pwd.c \
src/executor/command/exec_external_cmd.c \
src/executor/command/process_redir_list.c \
src/executor/pipeline/exec_pipeline.c \
src/executor/pipeline/exec_cmd_list.c \
src/executor/pipeline/wait_pids.c \
src/executor/exec_ast.c \
src/expander/command/expand/handler.c \
src/expander/command/quote_remove/quote_remove.c \
src/expander/command/to_char/generate_argv.c \
src/expander/command/word_split/word_split.c \
src/expander/command/word_split/split_token.c \
src/expander/common/utils.c \
src/expander/common/quote_remove_core.c \
src/expander/common/process_expansion_core.c \
src/expander/common/expand_variable.c \
src/expander/common/expand_single_token.c \
src/expander/redir/input_heredoc_content_handler.c \
src/expander/redir/redir_expand_handler.c \
src/expander/redir/redir_split_handler.c \
src/expander/redir/redir_quote_removal_handler.c \
src/expander/redir/generate_heredoc_file_handler.c \
src/expander/redir/generate_filename.c \
src/expander/expander.c \
src/minishell.c \
src/error.c \
