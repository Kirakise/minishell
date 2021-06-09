CC		=	gcc
HDRPATH =	../../includes/
CFLAGS	=	-Wall -Wextra -Werror -I$(HDRPATH)
HEADER	=	$(HDRPATH)libft.h
NAME	=	libft.a
SRCS	=	src/2list.c\
			src/ft_atoi.c\
			src/ft_bzero.c\
			src/ft_calloc.c\
			src/ft_isalnum.c\
			src/ft_itoa.c\
			src/ft_memmove.c\
			src/ft_putstr.c\
			src/ft_realloc.c\
			src/ft_split.c\
			src/ft_strdup.c\
			src/ft_strjoin.c\
			src/ft_substr.c\
			src/list.c\
			src/lst_to_arr.c\
			src/safe_free.c\
			src/string.c\

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
