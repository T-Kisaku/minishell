# Colors
PURPLE   = \033[38;5;141m
GREEN    = \033[38;5;46m
RESET    = \033[0m
BOLD     = \033[1m
CLEAR    = \r\033[K

# Project
NAME     = libft.a
SRC_DIR  = .
OBJ_DIR  = objs

SOURCES  = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c

BSOURCES = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJECTS     = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
BOBJECTS    = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(BSOURCES)))

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f
MKDIR_P = mkdir -p

# Rules
all: $(NAME)

$(NAME): $(OBJECTS)
	@$(AR) $@ $^
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}libft${RESET}] Build complete.\n"

bonus: $(OBJECTS) $(BOBJECTS)
	@$(AR) $(NAME) $^
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}libft (bonus)${RESET}] Bonus build complete.\n"

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR_P) $(OBJ_DIR)
	@printf "${CLEAR}${GREEN}•${RESET} Compiling ${notdir $<}...\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECTS) $(BOBJECTS)
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}libft${RESET}] Objects cleaned.\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "${CLEAR}${GREEN}✔${RESET} [${PURPLE}${BOLD}libft${RESET}] Library removed.\n"

re: fclean all

norm:
	@norminette $(addprefix $(SRC_DIR)/, $(SOURCES)) | grep -v "OK!" || true
	@norminette $(addprefix $(SRC_DIR)/, $(BSOURCES)) | grep -v "OK!" || true

format:
	c_formatter_42 $(addprefix $(SRC_DIR)/, $(SOURCES))
	c_formatter_42 $(addprefix $(SRC_DIR)/, $(BSOURCES))

.PHONY: all bonus clean fclean re
.SILENT: all clean fclean re bonus
