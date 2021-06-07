#include "../../includes/minishell.h"

static void	handle_quotes(int *q, int type)
{
	if (*q == 0)
		*q = type;
	else
		*q = 0;
}

static void	check_errors(t_err *err, int code)
{
	if (!code || err->val)
		return ;
	err->type = 1;
	if (code == 1)
		err->val = ft_strdup("\'");
	else if (code == 2)
		err->val = ft_strdup("\"");
	else
		err->val = ft_strdup("\\");
	if (!err->val)
		malloc_err();
}

static int	str_end(char c, int q, int mode)
{
	return (!c || (ft_isspace(c) && !q)
		|| (mode && ft_strchr(c, ";|><") && !q));
}

static void	add_char(char *str, int *i, char **s)
{
	*str = **s;
	*i += 1;
	*s += 1;
}

char	*parse_string(char *s, t_err *err, char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (!str_end(*s, q, 1))
	{
		if (*s == '\'' && q != 2)
			handle_quotes(&q, 1);
		else if (*s == '"' && q != 1)
			handle_quotes(&q, 2);
		else if (*s == '\\' && q != 1)
		{
			if (!str_end(*(s + 1), q, 0))
				add_char(str + i, &i, &s);
			else
				check_errors(err, 3);
		}
		add_char(str + i, &i, &s);
	}
	str[i] = 0;
	check_errors(err, q);
	return (s);
}
