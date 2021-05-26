#include "../../../includes/libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57));
}
int	ft_isalpha(int c)
{
	return (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)));
}

int	ft_isdigit(int c)
{
	return ((c >= 48) && (c <= 57));
}
