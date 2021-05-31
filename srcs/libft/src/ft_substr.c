#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*tmp;

	if (!s)
		return (0);
	ret = ft_calloc(len + 1, 1);
	if (ret == 0)
		return (0);
	if (start >= ft_strlen(s))
		return (ret);
	tmp = ret;
	s += start;
	while (*s && len--)
		*ret++ = *s++;
	*ret = 0;
	return (tmp);
}
