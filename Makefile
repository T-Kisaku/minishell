include mk/config.mk

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

NAME     = minishell
SRC_DIR  = src
OBJ_DIR  = obj
LIBFTDIR = libft
LIBFT    = $(LIBFTDIR)/libft.a

SRCS = \
src/utils/ms_string.c \
src/syntax_processor/tokenizer/process_special_char.c \
src/syntax_processor/tokenizer/processes.c \
src/syntax_processor/tokenizer/utils.c \
src/syntax_processor/tokenizer/tokenizer.c \
src/executor/executor.c \
src/minishell.c
OBJS = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))
PHONY_TARGETS = all clean fclean re


# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@$(MAKE) print_finished MSG="Minishell build complete"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) > /dev/null
	@$(MAKE) print_finished MSG="Libft build complete"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@$(MAKE) print_compiling TARGET="${notdir $<}"
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) print_finished MSG="Objects cleaned"
	

fclean:
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(MAKE) print_finished MSG="Objects cleaned"
	@$(RM) $(NAME)
	@$(MAKE) print_finished MSG="Execution file removed"

re: fclean all

include mk/testdata.mk
include mk/test.mk
include mk/dev.mk
include mk/print.mk

.PHONY: $(PHONY_TARGETS)
