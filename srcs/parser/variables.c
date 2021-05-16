#include "../../includes/minishell.h"

void	subst_vars(char **str)
{
	char	*s;
	char	*start;
	char	*var_name;
	char	*var_value;
	int		i;
	char	*res;
	char	*tmp;

	if (!str || !*str)
		return ;
	s = *str;
	res = ft_strdup("");//malloc
	tmp = 0;
	while (*s)
	{
		start = s;
		while (*s && *s != '$')
			s++;
		if (!*s)
			break ;
		//we should be in '$' now...
		i = 0;
		while (s[i + 1] && !ft_isspace(s[i + 1]))
			i++;
		var_name = ft_substr(s + 1, 0, i);//malloc
		var_value = find_var(var_name);//malloc
		free(var_name);
		*s = 0;// 0 instead of $
		tmp = ft_strjoin_3(res, start, var_value);//malloc
		free(res);
		free(var_value);
		res = tmp;
		tmp = 0;
		s += i + 1;
	}
	if (!*res)
	{
		free(res);
		return ;
	}
	free(*str);
	*str = res;
}
