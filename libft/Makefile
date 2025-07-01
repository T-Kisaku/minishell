include mk/config.mk
include mk/srcs.mk
# Project
NAME     = libft.a
SRC_DIR  = .
OBJ_DIR  = obj

# Rules
all: $(NAME)

$(NAME): $(SUBJECT_OBJS)
	@$(AR) $@ $^
	@$(MAKE) print_finished MSG="Libft build complete"

bonus: $(SUBJECT_OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="Bonus build complete"

string: $(STR_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="String build complete"

ctype: $(CTYPE_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="Ctype build complete"

stdio: $(STDIO_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="Stdio build complete"

stdlib: $(STDLIB_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="Stdlib build complete"

list: $(LIST_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="List build complete"

printf: $(SUBJECT_OBJS) $(PRINTF_OBJS)
	@$(AR) $(NAME) $^
	@$(MAKE) print_finished MSG="Printf build complete"



$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(MAKE) print_compiling TARGET="${notdir $<}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) print_finished MSG="Objects cleaned"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) print_finished MSG="Library removed"

re: fclean all

norm:
	@norminette . | grep -v "OK!" || true

format:
	c_formatter_42 $(addprefix $(SRC_DIR)/, $(SRCS))
	c_formatter_42 $(addprefix $(SRC_DIR)/, $(BONUS_SRCS))

include mk/print.mk

.PHONY: all bonus clean fclean re
.SILENT: all clean fclean re bonus

