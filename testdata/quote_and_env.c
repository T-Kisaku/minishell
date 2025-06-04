#include "testdata.h"

// Quote and environment variable handling

t_testdata echo_env_home(void)
{
    static char *argv[] = {"echo", "$HOME", NULL};
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
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo \"$HOME\"",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata echo_no_expand_home(void)
{
    static char *argv[] = {"echo", "$HOME", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 2 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo '$HOME'",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata echo_concat_user(void)
{
    static char *argv[] = {"echo", "hello'$USER'world", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 2 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo hello'$USER'world",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata export_and_echo(void)
{
    static char *argv1[] = {"export", "VAR=test", NULL};
    static char *argv2[] = {"echo", "$VAR", NULL};
    static t_command cmd1 = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = { .token_list = NULL, .argv = argv1, .argc = 2 }
    };
    static t_command cmd2 = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = { .token_list = NULL, .argv = argv2, .argc = 2 }
    };
    static t_and_or and_or1 = {
        .pipeline = { .commands = &cmd1, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_and_or and_or2 = {
        .pipeline = { .commands = &cmd2, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_list list2 = { .first_and_or = &and_or2, .next = NULL };
    static t_list list1 = { .first_and_or = &and_or1, .next = &list2 };
    return (t_testdata){
        .input = "export VAR=test ; echo $VAR",
        .token_list = {0},
        .ast = list1
    };
}

t_testdata echo_status(void)
{
    static char *argv[] = {"echo", "$?", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = { .token_list = NULL, .argv = argv, .argc = 2 }
    };
    static t_and_or and_or = {
        .pipeline = { .commands = &cmd, .cmd_count = 1 },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_ast ast = { .first_and_or = &and_or, .next = NULL };
    return (t_testdata){
        .input = "echo $?",
        .token_list = {0},
        .ast = ast
    };
}
