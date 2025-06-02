#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h" 
# include <stddef.h>	//for NULL,
# include <stdbool.h>	//for bool,	

//ast.hに構造体リストの型があればそれを使用しようと思ったが、よくわからなかったので一応自前で用意した。（また他の.hを変更するのが怖かったため。）

//クォート内の文字は特殊文字として扱われないため("<"の場合リダイレクトしない）、一つの列挙型で管理したほうが好ましいらしい。念の為"TOKEN_"とつけたが、なしでも良いと思う。
typedef enum
{
	TOKEN_UNQUOTED_WORD,
	TOKEN_SINGLE_QUOTED_WORD,
	TOKEN_DOUBLE_QUOTED_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_INPUT,    /* "<"   */
	TOKEN_REDIR_OUTPUT,   /* ">"   */
	TOKEN_REDIR_HERE_DOC, /* "<<"  */
	TOKEN_REDIR_APPEND,    /* ">>" */
	TOKEN_EOF	//"\0", これがあればparserのwhileループの条件式がやりやすいらしい
}					e_token_type;

//構造体リスト
typedef struct s_token
{
	char			*value;
	e_token_type	type;
	struct s_token	*next;
}					t_token;

//構造体リストを作成するために関数内で使用する構造体
typedef struct s_token_context
{
	t_token			**head;
	t_token			*cur_token;
	char			*start_str;
	char			*cur_str;
}					t_token_context;

//tokenizer.c
t_token		*tokenizer(char *string);
//processes.c
int		create_token(t_token_context *tc);
int		set_token(t_token_context *tc, e_token_type type);
void	process_space(t_token_context *tc);
int		process_quoted_word(t_token_context *tc);
int		process_unquoted_word(t_token_context *tc);
//process_special_char.c
int			process_special_char(t_token_context *lc);
//utils.c
int		write_error(char *msg);
void	clean_tokens(t_token **head);
int		ft_isspace(int c);

#endif