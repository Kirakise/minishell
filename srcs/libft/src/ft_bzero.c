#include "../../../includes/libft.h"

void ft_bzero(char *s, int size)
{
    while (size--)
        s[size] = 0;
}
