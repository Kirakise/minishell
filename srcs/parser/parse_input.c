#include "../../includes/minishell.h"

static void	handle_quotes(int *val)
{
	if (*val == 0)
		*val = 1;
	else
		*val = 0;
}

static char	*check_close_quotes(int single, int dbl)
{
	char	*res;

	if (single)
		res = ft_strdup("\'");
	else if (dbl)
		res = ft_strdup("\"");
	else
		return (0);
	if (!res)
		malloc_err();
	return (res);
}

static char	*str_iter(char *s, char **err, char *str)
{
	int	i;
	int	q[2];
	int	bslash;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (*s && (!ft_isspace(*s) || q[0] || q[1])
		&& (!ft_strchr(*s, ";|><") || bslash || q[0] || q[1]))
	{
		bslash = 0;
		if (*s == '\'' && !q[1] && !bslash)
			handle_quotes(&q[0]);
		else if (*s == '"' && !q[0] && !bslash)
			handle_quotes(&q[1]);
		else if (*s == '\\' && s[1] && !q[0] && !q[1])
			bslash = 1;
		str[i] = *s;
		i++;
		s++;
	}
	str[i] = 0;
	*err = check_close_quotes(q[0], q[1]);
	return (s);
}

char	*parse_input(char **input, char **err)
{
	char	*str;
	char	*tmp;

	while (ft_isspace(**input))
		*input += 1;
	str = malloc(sizeof(char) * (ft_strlen(*input) + 1));
	if (!str)
		malloc_err();
	*input = str_iter(*input, err, str);
	tmp = ft_strdup(str);
	if (!tmp)
		malloc_err();
	free(str);
	while (ft_isspace(**input))
		*input += 1;
	return (tmp);
}
