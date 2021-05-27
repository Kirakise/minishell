#include "../../includes/minishell.h"

int	var_isvalid(char *str, int cmd_type)
{
	if (!*str || (!ft_isalpha(*str) && !(*str == '_')))
		return (0);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (!cmd_type && *str == '+')
		str++;
	if (*str && (*str != '=' || (cmd_type && *str == '=')))
		return (0);
	return (1);
}
