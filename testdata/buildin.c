#include "testdata.h"

// Builtin command edge cases

t_testdata cd_noarg(void)
{
    static char *argv[] = {"cd", NULL};
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
        .input = "cd",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata cd_non_existing_dir(void)
{
    static char *argv[] = {"cd", "non_existing_dir", NULL};
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
        .input = "cd non_existing_dir",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata export_two_vars(void)
{
    static char *argv[] = {"export", "VAR1=hello", "VAR2=world", NULL};
    static t_command cmd = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = {
            .token_list = NULL,
            .argv = argv,
            .argc = 3
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
        .input = "export VAR1=hello VAR2=world",
        .token_list = {0},
        .ast = ast
    };
}

t_testdata unset_then_echo(void)
{
    static char *argv1[] = {"unset", "VAR1", NULL};
    static t_command cmd1 = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = {
            .token_list = NULL,
            .argv = argv1,
            .argc = 2
        }
    };
    static char *argv2[] = {"echo", "$VAR1", NULL};
    static t_command cmd2 = {
        .type = CMD_SIMPLE,
        .redirs = NULL,
        .redir_count = 0,
        .u.simple = {
            .token_list = NULL,
            .argv = argv2,
            .argc = 2
        }
    };
    static t_and_or and_or1 = {
        .pipeline = {
            .commands = &cmd1,
            .cmd_count = 1
        },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_and_or and_or2 = {
        .pipeline = {
            .commands = &cmd2,
            .cmd_count = 1
        },
        .op_next = OP_NONE,
        .next = NULL
    };
    static t_list list2 = {
        .first_and_or = &and_or2,
        .next = NULL
    };
    static t_list list1 = {
        .first_and_or = &and_or1,
        .next = &list2
    };
    return (t_testdata){
        .input = "unset VAR1 ; echo $VAR1",
        .token_list = {0},
        .ast = list1
    };
}

t_testdata exit_status_42(void)
{
    static char *argv[] = {"exit", "42", NULL};
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
        .input = "exit 42",
        .token_list = {0},
        .ast = ast
    };
}
