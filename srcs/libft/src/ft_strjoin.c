#include "../../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	str -= len;
	return (str);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2 || !s3)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	while (*s3)
		*str++ = *s3++;
	*str = 0;
	str -= len;
	return (str);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	int		space;

	if (!s1 || !s2)
		return (0);
	space = 1;
	if (ft_strlen(s1) == 0)
		space = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + space;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (*s1)
		*str++ = *s1++;
	if (space)
		*str++ = ' ';
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	str -= len;
	return (str);
}
