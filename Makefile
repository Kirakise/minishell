CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard srcs/*.c srcs/foncs/*.c srcs/libft/src/*.c srcs/parser/*.c srcs/utils/*.c)
OBJS = $(SRCS:%.c=%.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)
fclean: clean
	rm $(NAME)
re: fclean all
