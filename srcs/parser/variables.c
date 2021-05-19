#include "../../includes/minishell.h"

extern t_shell	g_shell;

static char	*get_var_value(char *s, int *i)
{
	char	*name;
	char	*value;

	if (*i == 0 && s[*i] == '?')
	{
		*i += 1;
		return (ft_itoa(g_shell.status));//malloc
	}
	if (*i == 0)
		return (ft_strdup("$"));
	name = ft_substr(s, 0, *i);//malloc
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
		while (*s && *s != '$')
			s++;
		while (*s == '$')
			s++;
		if (!*s)
			tmp = ft_strjoin(*res, start);//malloc
		else
		{
			i = 0;
			while (ft_isalnum(s[i]))
				i++;
			var = get_var_value(s, &i);//malloc
			*(s - 1) = 0;// 0 instead of $
			tmp = ft_strjoin_3(*res, start, var);//malloc
			free(var);
			s += i;
		}
		free(*res);
		*res = tmp;
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
