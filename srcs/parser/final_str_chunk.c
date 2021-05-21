#include "../../includes/minishell.h"

static void	handle_quotes(int *q, int type)
{
	if (*q == 0)
		*q = type;
	else
		*q = 0;
}

static int str_iterate(char **s, char *str, int var)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (**s && !var)
	{
		if (**s == '\'' && q != 2)
			handle_quotes(&q, 1);
		else if (**s == '"' && q != 1)
			handle_quotes(&q, 2);
		else if (**s == '$' && q != 1)
			var = 1;
		else
		{
			if (**s == '\\' && !q && (**s + 1))
				*s += 1;
			str[i] = **s;
			i++;
		}
		*s += 1;
	}
	str[i] = 0;
	return (var);
}

int	parse_str_chunk(char **input, char **res)
{
	int		var;

	*res = malloc(sizeof(char) * (ft_strlen(*input) + 1));//malloc
	if (!*res)
		return (-1);//
	var = 0;
	return (str_iterate(input, *res, var));
}
