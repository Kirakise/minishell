#include "../../../includes/libft.h"

void	ft_realloc(char **s1, char *s2)
{
	char	*ret;
	int		i;

	if (!*s1)
		return ;
	i = ft_strlen(*s1);
	ret = calloc(i + 2, 1);
	ft_memmove(ret, *s1, i);
	ret[i] = s2[0];
	if (*s1)
		free(*s1);
	*s1 = ret;
}
