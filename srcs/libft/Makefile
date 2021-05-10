CC		=	gcc
HDRPATH =	../../includes/
CFLAGS	=	-Wall -Wextra -Werror -I./ -I$(HDRPATH)
HEADER	=	$(HDRPATH)libft.h get_next_line.h
NAME	=	libft.a
SRCS	=	src/ft_memmove.c\
			src/ft_bzero.c\
			src/ft_calloc.c\
			src/ft_realloc.c\
			src/ft_strjoin.c\
			src/get_next_line.c\
			src/get_next_line_utils.c\
			src/string.c\
			src/list.c\
			src/ft_putstr.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) Makefile
			ar rcs $(NAME) $(OBJS)

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
