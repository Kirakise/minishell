#include "minishell.h"

int	init_struct(void)
{
	g_shell.fd_1 = 1;
	g_shell.fd_0 = 0;
	g_shell.tmp_fd_1 = dup(g_data.fd_1);
	g_shell.tmp_fd_0 = dup(g_data.fd_0);
}

char	**envcpy(char **line)
{
	char	**res;
	int	i;

	i = 0;
	while (line[i])
		i++;
	if(!res = malloc(sizeof(char *) * i))
		return (0);
	res[i] = 0;
	i = 0;
	while (line[i])
		res[i] = ft_strdup(line[i]);
	return (res);
}

size_t		ft_strlen(const char *s)
{
	size_t				i;
	const unsigned char		*s1;

	s1 = (const unsigned char *)s;
	i = 0;
	while (*s1++)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int	size;
	char	*ret;
	char	*tmp2;

	tmp2 = (char *)s1;
	size = ft_strlen(tmp2);
	ret = malloc(sizeof(char) * size + 1);
	if (ret == 0)
		return (0);
	tmp2 = ret;
	while (*s1)
		*tmp2++ = *s1++;
	*tmp2 = '\0';
	return (ret);
}
