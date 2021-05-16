#include "../../includes/minishell.h"

static char	*get_var_value(char *s, int i)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(s + 1, 0, i);//malloc
	var_value = find_var(var_name);//malloc
	free(var_name);
	return (var_value);
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
		i = 0;//we should be in '$' now...
		while (s[i + 1] && !ft_isspace(s[i + 1]))
			i++;
		var_value = get_var_value(s, i);
		*s = 0;// 0 instead of $
		tmp = ft_strjoin_3(*res, start, var_value);//malloc
		free(*res);
		free(var_value);
		*res = tmp;
		tmp = 0;
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
