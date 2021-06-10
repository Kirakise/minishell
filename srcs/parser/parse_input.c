#include "../../includes/minishell.h"

char	*parse_input(char **input, t_err *err)
{
	char	*str;
	char	*tmp;

	while (ft_isspace(**input))
		*input += 1;
	if (**input == ';')
	{
		err->val = ft_strdup(";");
		if (!err->val)
			malloc_err();
	}
	str = malloc(sizeof(char) * (ft_strlen(*input) + 1));
	if (!str)
		malloc_err();
	*input = parse_string(*input, err, str);
	tmp = ft_strdup(str);
	if (!tmp)
		malloc_err();
	free(str);
	while (ft_isspace(**input))
		*input += 1;
	return (tmp);
}
