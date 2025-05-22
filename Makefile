include mk/config.mk
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

print_finished:
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}$(NAME)${RESET}] $(MSG)\n"
print_compiling:
	@printf "${CLEAR}${GREEN}•${RESET} Compiling $(TARGET)...\n"
print_running:
	@printf "${CLEAR}${GREEN}🏃 ${RESET} Running $(TARGET)...\n"

.PHONY: all clean fclean re print_finished

