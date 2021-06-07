CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -Iincludes/ -g -fsanitize=address
SRCS	= srcs/main.c\
		srcs/errors/error.c\
		srcs/foncs/cd.c\
		srcs/foncs/do_coms.c\
		srcs/foncs/do_coms2.c\
		srcs/foncs/do_redirect.c\
		srcs/foncs/echo.c\
		srcs/foncs/env.c\
		srcs/foncs/execve.c\
		srcs/foncs/exit.c\
		srcs/foncs/export.c\
		srcs/foncs/pwd.c\
		srcs/foncs/unset.c\
		srcs/foncs/var_validation.c\
		srcs/parser/check_export_redir.c\
		srcs/parser/final_parse.c\
		srcs/parser/final_str_chunk.c\
		srcs/parser/get_commands.c\
		srcs/parser/parse_cmd_args.c\
		srcs/parser/parse_input.c\
		srcs/parser/parse_redir_pipe.c\
		srcs/temp/history.c\
		srcs/temp/tmpread.c\
		srcs/termcaps/setflags.c\
		srcs/utils/utils1.c
OBJS	= $(SRCS:.c=.o)
HEADERS = includes/libft.h includes/minishell.h
LFT_DIR = srcs/libft/
LIBFT	= $(LFT_DIR)libft.a
NAME	= minishell

all: lft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(LFT_DIR) -lft -ltermcap -o $(NAME)

%.o: %.c $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

lft:
	@$(MAKE) -j -C $(LFT_DIR)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus lft
