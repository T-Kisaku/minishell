#include "testdata.h"

// Pipe related commands

t_testdata ls_pipe_grep(void)
{
    static char *argv1[] = {"ls", NULL};
    static char *argv2[] = {"grep", ".c", NULL};
    static t_command cmds[] = {
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv1, .argc = 1 }
        },
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv2, .argc = 2 }
        }
    };
    static t_and_or and_or = {
        .pipeline = {
            .commands = cmds,
            .cmd_count = 2
        },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "ls | grep .c",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata cat_makefile_pipe_wc_l(void)
{
    static char *argv1[] = {"cat", "Makefile", NULL};
    static char *argv2[] = {"wc", "-l", NULL};
    static t_command cmds[] = {
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv1, .argc = 2 }
        },
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv2, .argc = 2 }
        }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = cmds, .cmd_count = 2 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "cat Makefile | wc -l",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata ls_pipe_grep_pipe_wc(void)
{
    static char *argv1[] = {"ls", NULL};
    static char *argv2[] = {"grep", ".h", NULL};
    static char *argv3[] = {"wc", "-l", NULL};
    static t_command cmds[] = {
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv1, .argc = 1 }
        },
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv2, .argc = 2 }
        },
        {
            .type = CMD_SIMPLE,
            .redirs = NULL,
            .redir_count = 0,
            .u.simple = { .token_list = NULL, .argv = argv3, .argc = 2 }
        }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = cmds, .cmd_count = 3 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "ls | grep .h | wc -l",
        .token_list = {0},
        .ast = ast
    };
}
