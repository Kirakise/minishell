#include "../../../includes/libft.h"

void ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

void ft_puendl(const char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}
