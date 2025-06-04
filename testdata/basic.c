#include "testdata.h"

// Basic command execution

t_testdata ls(void)
{
    static char *argv[] = {"ls", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = {
            .token_list = NULL,
            .argv = argv,
            .argc = 1
        }
    };
    static t_and_or and_or = {
        .pipeline = {
            .commands = &cmd,
            .cmd_count = 1
        },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = {
        .first_and_or = &and_or,
        .next = NULL
    };
    return (t_testdata){
        .input = "ls",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata echo_hello(void)
{
    static char *argv[] = {"echo", "hello", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = {
            .token_list = NULL,
            .argv = argv,
            .argc = 2
        }
    };
    static t_and_or and_or = {
        .pipeline = {
            .commands = &cmd,
            .cmd_count = 1
        },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = {
        .first_and_or = &and_or,
        .next = NULL
    };
    return (t_testdata){
        .input = "echo hello",
        .token_list = {0},
        .ast = ast
    };
}
