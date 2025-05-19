#ifndef MINISHELL_H
#define MINISHELL_H


typedef struct s_ast
{
	char *left;
	char *right;
} t_ast;

typedef struct data
{
	char **lexered;
	t_ast *parsered;
} t_data;



char** lexer(char **argv);
void parser();
void executor();

void cleanup(t_data data);
void error();

#endif