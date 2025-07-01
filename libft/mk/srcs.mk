SUBJECT_SRCS  = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c
SUBJECT_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SUBJECT_SRCS))

BONUS_SRCS = \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BONUS_SRCS))

STR_SRCS = \
	ft_strchr.c \
	ft_strdup.c \
	ft_strndup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_split.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c  \
	ft_strreduce.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c
STR_OBJS     = $(patsubst %.c, $(OBJ_DIR)/%.o, $(STR_SRCS))


CTYPE_SRCS =  \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_isspace.c \
ft_tolower.c \
ft_toupper.c 
CTYPE_OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(CTYPE_SRCS))


STDIO_SRCS =  \
ft_fputs.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_puts.c \
ft_putstr_fd.c
STDIO_OBJS   = $(patsubst %.c, $(OBJ_DIR)/%.o, $(STDIO_SRCS))


STDLIB_SRCS =  \
ft_atoi.c \
ft_calloc.c \
ft_itoa.c \
ft_realloc.c
STDLIB_OBJS  = $(patsubst %.c, $(OBJ_DIR)/%.o, $(STDLIB_SRCS))


LIST_SRCS =  \
ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstfind.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c \
ft_lstunset.c \
ft_lst_is_last.c \
ft_lstinsert.c
LIST_OBJS    = $(patsubst %.c, $(OBJ_DIR)/%.o, $(LIST_SRCS))


PRINTF_SRCS =  \
ft_printf/add_bytes.c \
ft_printf/ft_printf.c \
ft_printf/put_char.c \
ft_printf/put_hex.c \
ft_printf/put_int.c \
ft_printf/put_pointer.c \
ft_printf/put_string.c \
ft_printf/put_unsigned_int.c
PRINTF_OBJS  = $(patsubst %.c, $(OBJ_DIR)/%.o, $(PRINTF_SRCS))
