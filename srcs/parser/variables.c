#include "../../includes/minishell.h"

static char	*get_var_value(char *s, int i)
{
	char	*name;
	char	*value;

	name = ft_substr(s, 0, i);//malloc
	value = find_var(name);//malloc
	free(name);
	return (value);
}

static void	str_iterate(char *s, char **res)
{
	char	*start;
	char	*var_value;
	char	*tmp;
	int		i;

	while (*s)
	{
		start = s;
		while (*s && *s != '$')
			s++;
		if (!*s)
			return ;
		while (*s == '$')
			s++;
		i = 0;
		while (s[i] && s[i] != '$' && !ft_isspace(s[i]))
			i++;
		if (i == 0)
			var_value = ft_strdup("$");
		else
			var_value = get_var_value(s, i);
		s--;
		*s = 0;// 0 instead of $
		tmp = ft_strjoin_3(*res, start, var_value);//malloc
		free(*res);
		free(var_value);
		*res = tmp;
		s += i + 1;
	}
}

void	subst_vars(char **str)
{
	char	*s;
	char	*res;

	if (!str || !*str)
		return ;
	s = *str;
	res = ft_strdup("");//malloc
	str_iterate(s, &res);
	if (!*res)
		free(res);
	else
	{
		free(*str);
		*str = res;
	}
}
