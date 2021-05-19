#include "../../../includes/libft.h"

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int)(-n));
	return ((unsigned int)n);
}

static int	ft_getlen(unsigned int n)
{
	int				len;
	unsigned int	num;

	len = 0;
	num = n;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	if (len == 0)
		len = 1;
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	int				sign;
	unsigned int	num;

	sign = 0;
	if (n < 0)
		sign = 1;
	num = ft_abs(n);
	len = ft_getlen(num) + sign;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len--] = 0;
	while (len >= 0 + sign)
	{
		str[len] = num % 10 + 48;
		len--;
		num = num / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
