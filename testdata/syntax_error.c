#include "testdata.h"

// Syntax error cases

t_testdata err_unclosed_quote(void)
{
    return (t_testdata){
        .input = "echo \"unclosed",
        .token_list = {0},
        .ast = {0}
    };
}

t_testdata err_bad_redir(void)
{
    return (t_testdata){
        .input = "cat <",
        .token_list = {0},
        .ast = {0}
    };
}

t_testdata err_pipe_position(void)
{
    return (t_testdata){
        .input = "| ls",
        .token_list = {0},
        .ast = {0}
    };
}

t_testdata err_single_redirect(void)
{
    return (t_testdata){
        .input = ">",
        .token_list = {0},
        .ast = {0}
    };
}
