#include "libft.h"

void	ft_bzero(char *s, int size)
	{
	while (size > 0)
	{
		size--;
		s[size] = 0;
	}
}
