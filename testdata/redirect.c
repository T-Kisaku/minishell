#include "testdata.h"

// Redirection examples

t_testdata redir_output(void)
{
    static char *argv[] = {"echo", "hello", NULL};
    static t_redir redirs[] = {
        { .type = REDIR_OUTPUT, .target = "out.txt" }
    };
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = redirs,
        .redir_count = 1,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 2 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo hello > out.txt",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata redir_input(void)
{
    static char *argv[] = {"cat", NULL};
    static t_redir redirs[] = { { .type = REDIR_INPUT, .target = "out.txt" } };
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = redirs,
        .redir_count = 1,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 1 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "cat < out.txt",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata redir_append(void)
{
    static char *argv[] = {"echo", "bye", NULL};
    static t_redir redirs[] = { { .type = REDIR_APPEND, .target = "out.txt" } };
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = redirs,
        .redir_count = 1,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 2 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo bye >> out.txt",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata redir_mix(void)
{
    static char *argv[] = {"cat", NULL};
    static t_redir redirs[] = {
        { .type = REDIR_INPUT, .target = "out.txt" },
        { .type = REDIR_OUTPUT, .target = "new.txt" }
    };
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = redirs,
        .redir_count = 2,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 1 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "cat < out.txt > new.txt",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata pipe_to_redir(void)
{
    static char *argv1[] = {"echo", "test", NULL};
    static char *argv2[] = {"cat", NULL};
    static t_redir redirs2[] = { { .type = REDIR_OUTPUT, .target = "result.txt" } };
    static t_command cmds[] = {
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv1, .argc = 2 }
        },
        {
            .type = CMD_SIMPLE,
            .redirs = redirs2,
            .redir_count = 1,
            .u.simple = { .token_list = NULL, .argv = argv2, .argc = 1 }
        }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = cmds, .cmd_count = 2 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo test | cat > result.txt",
        .token_list = {0},
        .ast = ast
    };
}
