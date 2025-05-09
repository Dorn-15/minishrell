NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror 
LFLAGS=-lreadline

SRCS = src/main.c \
	src/path.c \
	src/read.c \
	src/write.c \
	src/mem.c \
	src/env/env_utile.c \
	src/env/env_utile2.c \
	src/cmd/env/env.c \
	src/cmd/env/env_err.c \
	src/cmd/exit.c \
	src/cmd/pwd.c \
	src/cmd/export/export.c \
	src/cmd/export/export_sort.c \
	src/cmd/export/export_add.c \
	src/cmd/export/export_add_with_equal.c \
	src/cmd/unset/unset.c \
	src/cmd/cd/cd.c \
	src/cmd/cd/cd_err_1.c \
	src/cmd/cd/cd_err_2.c \
	src/cmd/cd/cd_env.c \
	src/cmd/echo.c \
	src/parsing/parsing_utils.c src/parsing/parsing.c src/parsing/error_pars_handle.c\
	src/parsing/special_case_pars.c \
	src/lexing/lex_split.c src/lexing/lexer.c src/lexing/utils_lexer.c \
	src/expand/expand.c src/expand/expand_utils.c src/expand/split_expand.c \
	src/clear/clear_param.c src/clear/error_pars.c \
	src/exec/here_doc.c src/exec/pipe.c src/exec/pipe_utils.c src/exec/child_utils.c src/exec/here_doc_utils.c\
	src/signal/signal_parent.c \
	src/signal/signal_child.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LFLAGS)

$(LIBFT):
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
