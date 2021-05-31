#include "libft.h"

static size_t	get_num_words(char const *s, char c)
{
	size_t		tmp;
	size_t		ret;

	ret = 0;
	tmp = 1;
	while (*s)
	{
		if (*s == c)
		{
			if (tmp == 0)
				ret++;
			tmp = 1;
		}
		else
			tmp = 0;
		s++;
	}
	if (tmp == 0)
		ret++;
	return (ret);
}

static char	*get_new_word(char **s, char c)
{
	size_t	i;
	char	*tmp;

	while (**s == c && **s != 0)
		(*s)++;
	i = 0;
	tmp = *s;
	while (tmp[i] != c && tmp[i] != 0)
		i++;
	tmp = ft_substr(*s, 0, i);
	while (**s != c && **s != 0)
		(*s)++;
	return (tmp);
}

static void	clean_all(char **s)
{
	size_t	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}

static char	**ft_split2(char const *str, char **ret, char c, long i)
{
	long	j;
	char	*s;

	s = (char *)str;
	j = 0;
	while (j < i)
	{
		ret[j] = get_new_word(&s, c);
		if (ret[j] == 0)
		{
			clean_all(ret);
			free(ret);
			return (0);
		}
		j++;
	}
	return (ret);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	long	i;

	if (str == 0)
		return (0);
	i = get_num_words(str, c);
	ret = ft_calloc(i + 1, sizeof(char **));
	if (ret == 0)
		return (0);
	return (ft_split2(str, ret, c, i));
}
