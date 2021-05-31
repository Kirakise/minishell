#include "../../includes/minishell.h"

int	parse_command(char **s, t_cmd *cmd, t_list **arg_list)
{
	char	*str;

	cmd->exec_name = parse_input(s, &cmd->error);
	if (cmd->error)
		return (1);
	str = ft_strdup(cmd->exec_name);
	if (!str)
		malloc_err();
	ft_lstadd_back(arg_list, ft_lstnew(str));
	return (0);
}

int	parse_arguments(char **s, t_cmd *cmd, t_list **arg_list)
{
	char	*str;

	while (**s && !ft_strchr(**s, ";|><"))
	{
		str = 0;
		str = parse_input(s, &cmd->error);
		if (cmd->error)
			return (1);
		if (*str)
			ft_lstadd_back(arg_list, ft_lstnew(str));
		else
			free(str);
	}
	return (0);
}
