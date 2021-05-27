#include "../../includes/minishell.h"

int	var_isvalid(char *str)
{
	if (!*str || (!ft_isalpha(*str) && !(*str == '_')))
		return (0);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str && *str != '=')
		return (0);
	return (1);
}
