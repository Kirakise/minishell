#include "../../includes/minishell.h"

int	parse_command(char **s, t_cmd *cmd, t_list **arg_list)
{
	char	*str;

	cmd->exec_name = parse_input(s, &cmd->error);//malloc
	if (cmd->error)
		return (1);//return err
	str = ft_strdup(cmd->exec_name);//malloc
	ft_lstadd_back(arg_list, ft_lstnew(str));
	return (0);
}

int	parse_arguments(char **s, t_cmd *cmd, t_list **arg_list)
{
	char	*str;

	while (**s && !ft_strchr(**s, ";|><"))
	{
		str = 0;
		str = parse_input(s, &cmd->error);//malloc
		if (cmd->error)
			return (1);//return err
		if (*str)
			ft_lstadd_back(arg_list, ft_lstnew(str));
		else
			free(str);
	}
	return (0);
}
