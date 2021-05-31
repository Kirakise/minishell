CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes/ -g
SRCS = $(wildcard srcs/*.c srcs/foncs/*.c srcs/parser/*.c srcs/utils/*.c srcs/temp/*.c srcs/termcaps/*.c srcs/errors/*.c)
OBJS = $(SRCS:%.c=%.o)
HEADERS = $(INC)libft.h $(INC)minishell.h
LFT_DIR = srcs/libft/
LIBFT =	$(LFT_DIR)libft.a
NAME = minishell

ifdef FSANITIZE
CFLAGS += -fsanitize=address
endif

all: lft $(NAME)

asan:
	$(MAKE) FSANITIZE=1 all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(LFT_DIR) -lft -ltermcap -o $(NAME)

linux: $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(LFT_DIR) -lncurses -o $(NAME)

%.o: %.c $(HEADERS) $(LIBFT) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

lft:
	@$(MAKE) -j -C $(LFT_DIR)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all
