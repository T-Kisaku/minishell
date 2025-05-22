include mk/config.mk

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@(MAKE) print_msg MSG="Build complete"

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) > /dev/null
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}$(NAME)${RESET}] Libft build complete\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) -r $(OBJ_DIR)

fclean:
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(NAME)

re: fclean all

TEST_MK := mk/test.mk
test:
	@$(MAKE) -f $(TEST_MK) all

test_%:
	@$(MAKE) -f $(TEST_MK) $*


DEV_MK := mk/dev.mk
dev:
	@$(MAKE) -f $(DEV_MK) all

dev_%:
	@$(MAKE) -f $(DEV_MK) $*

.PHONY: all clean fclean re
