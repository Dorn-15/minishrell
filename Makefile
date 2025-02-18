NAME = minishell

CC = gcc
CFLAGS = -g -o -Wall -Wextra -Werror

SRCS = src/main.c \
	src/path.c \
	src/read.c \
	src/write.c \
	src/env_utile.c \
	src/mem.c \
	src/cmd/env/env.c \
	src/cmd/env/env_err.c \
	src/cmd/exit.c \
	src/cmd/pwd.c \
	src/cmd/export/export.c \
	src/cmd/export/export_sort.c \
	src/cmd/export/export_add.c \
	src/cmd/unset/unset.c \
	src/cmd/cd/cd.c \
	src/cmd/cd/cd_err_1.c \
	src/cmd/cd/cd_err_2.c \
	src/cmd/cd/cd_env.c \
	src/cmd/echo.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

libft:
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re libft
