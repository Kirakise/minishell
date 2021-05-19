#include "../../includes/minishell.h"

static char	*get_var_value(char *s, int i)
{
	char	*name;
	char	*value;

	if (i == 0)
		return (ft_strdup("$"));
	name = ft_substr(s, 0, i);//malloc
	value = find_var(name);//malloc
	free(name);
	return (value);
}

static void	str_iterate(char *s, char **res)
{
	char	*start;
	char	*var;
	char	*tmp;
	int		i;

	while (*s)
	{
		start = s;
//		printf("start = %s\n", start);
		while (*s && *s != '$')
			s++;
		if (!*s)
		{
			tmp = ft_strjoin(*res, start);//malloc
			free(*res);
			*res = tmp;
			return ;
		}
		while (*s == '$')
			s++;
		i = 0;
		while (ft_isalnum(s[i]))
			i++;
		var = get_var_value(s, i);
		*(s - 1) = 0;// 0 instead of $
		tmp = ft_strjoin_3(*res, start, var);//malloc
		free(*res);
		free(var);
		*res = tmp;
		s += i;
	}
}

void	subst_vars(char **str)
{
	char	*res;

	if (!str || !*str)
		return ;
	res = ft_strdup("");//malloc
	str_iterate(*str, &res);
	free(*str);
	*str = res;
}
