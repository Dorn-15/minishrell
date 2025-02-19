NAME = libft.a

HEADERS = include/libft.h

SRCS_DIR = src/

LIB = ft_abs.c \
	ft_atoi.c \
	ft_atoi_ull.c \
	ft_atoi_uch.c \
	ft_atof.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c
LIB_SRC = $(addprefix $(SRCS_DIR)lib/, $(LIB))

LST = ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c
LST_SRC = $(addprefix $(SRCS_DIR)list/, $(LST))

PRTF = ft_printf.c \
	ft_print_base.c \
	ft_print_address.c \
	ft_print_unsigned.c \
	ft_print_str.c \
	ft_print_nbr.c \
	ft_print_hex.c \
	ft_print_char.c
PRTF_SRC = $(addprefix $(SRCS_DIR)printf/, $(PRTF))

GNL = get_next_line.c \
	get_next_line_utils.c
GNL_SRC = $(addprefix $(SRCS_DIR)gnl/, $(GNL))

SRCS = $(LIB_SRC) $(LST_SRC) $(PRTF_SRC) $(GNL_SRC)


OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -I $(SRCS_DIR)

AR = ar -rcs
RM = rm -f

%.o: $(SRCS_DIR)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
