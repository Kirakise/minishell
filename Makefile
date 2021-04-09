SRCS = $(wildcard srcs/*.c srcs/foncs/*.c srcs/libft/*.c srcs/parser/*.c srcs/utils/*.c)
OBJS = $(SRCS:%.c=%.o)
NAME = minishell


all: $(OBJS)
	gcc $^ -o $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -g -Iincludes $^ -o $@

clean:
	rm $(OBJS)
fclean: clean
	rm $(NAME)
re: fclean all