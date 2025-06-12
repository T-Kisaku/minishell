SRCS = \
src/utils/ms_string.c \
src/utils/token.c \
src/utils/ast/and_or.c \
src/utils/ast/redir.c \
src/utils/ast/command.c \
src/executor/command/buildin/echo.c \
src/executor/command/buildin/env.c \
src/executor/command/buildin/exit.c \
src/executor/command/buildin/export.c \
src/executor/command/buildin/pwd.c \
src/executor/command/buildin/unset.c \
src/executor/command/buildin/cd.c \
src/executor/command/buildin/exec_builtin_cmd.c \
src/executor/command/exec_external_cmd.c \
src/executor/command/process_redir_list.c \
src/executor/pipeline/wait_pids.c \
src/executor/pipeline/exec_pipeline.c \
src/executor/pipeline/exec_cmd_list.c \
src/executor/exec_ast.c \
src/minishell.c
