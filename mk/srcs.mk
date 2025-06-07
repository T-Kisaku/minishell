SRCS = \
src/utils/ms_string.c \
src/utils/token.c \
src/syntax_processor/ast_builder/ast_builder.c \
src/syntax_processor/expander/expander.c \
src/syntax_processor/tokenizer/processes.c \
src/syntax_processor/tokenizer/tokenizer.c \
src/syntax_processor/tokenizer/utils.c \
src/syntax_processor/tokenizer/process_special_char.c \
src/minishell.c \
src/executor/buildin/cd.c \
src/executor/buildin/echo.c \
src/executor/buildin/env.c \
src/executor/buildin/exec_buildin.c \
src/executor/buildin/exit.c \
src/executor/buildin/export.c \
src/executor/buildin/pwd.c \
src/executor/buildin/unset.c \
src/executor/command/process_redirs.c \
src/executor/command/run_command.c \
src/executor/exec_ast.c \
src/executor/pipeline/run_pipeline.c \
src/executor/pipeline/run_pipes.c \
src/executor/pipeline/wait_pids.c
