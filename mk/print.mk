PHONY_TARGETS += print_finished print_compiling print_running
print_finished:
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}$(NAME)${RESET}] $(MSG)\n"
print_compiling:
	@printf "${CLEAR}${GREEN}•${RESET} Compiling $(TARGET)...\n"
print_running:
	@printf "${CLEAR}${GREEN}🏃 ${RESET} Running $(TARGET)...\n"
