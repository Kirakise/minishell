CC = gcc
INC = includes/
CFLAGS = -Wall -Wextra -Werror -I$(INC) -g -fsanitize=address
SRCS = $(wildcard srcs/*.c srcs/foncs/*.c srcs/libft/src/*.c srcs/parser/*.c srcs/utils/*.c srcs/temp/*.c srcs/termcaps/*.c)
OBJS = $(SRCS:%.c=%.o)
HEADERS = $(INC)libft.h $(INC)minishell.h
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -ltermcap -o $(NAME)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS)
fclean: clean
	rm $(NAME)
re: fclean all
