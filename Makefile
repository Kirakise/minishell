SRCS = $(wildcard srcs/*.c srcs/foncs/*.c srcs/libft/src/*.c srcs/parser/*.c srcs/utils/*.c)
OBJS = $(SRCS:%.c=%.o)
NAME = minishell


$(NAME): $(OBJS)
	gcc $^ -o $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -g -c $^ -o $@

clean:
	rm $(OBJS)
fclean: clean
	rm $(NAME)
re: fclean all
