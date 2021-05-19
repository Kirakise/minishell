#include "../../includes/minishell.h"

extern t_shell	g_shell;

static char	*get_var_value(char *s, int *i)
{
	char	*name;
	char	*value;

	if (*i == 0)
	{
		if (s[*i] != '?')
			return (ft_strdup("$"));
		*i += 1;
		return (ft_itoa(g_shell.status));
	}
	name = ft_substr(s, 0, *i);
	if (!name)
		return (0);
	value = find_var(name);
	free(name);
	return (value);
}

static char	*var_subst(char **str, char *start, char **res)
{
	int		i;
	char	*s;
	char	*var;
	char	*tmp;

	s = *str;
	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	var = get_var_value(s, &i);//malloc
	*(s - 1) = 0;// 0 instead of $
	tmp = ft_strjoin_3(*res, start, var);//malloc
	free(var);
	s += i;
	*str = s;
	return (tmp);
}

static void	str_iterate(char *s, char **res)
{
	char	*start;
	char	*tmp;

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
			tmp = var_subst(&s, start, res);
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
