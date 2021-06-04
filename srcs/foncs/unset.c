#include "../../includes/minishell.h"

extern t_shell	g_shell;

void	del_var(char *s)
{
	int		i;
	int		found;
	char	**ret;

	i = 0;
	found = 0;
	while (g_shell.env[i])
		i++;
	ret = calloc(i, sizeof(char *));
	i = 0;
	while (g_shell.env[i + found])
	{
		if (!found && !ft_strncmp(s, g_shell.env[i], ft_strlen(s)))
		{
			free(g_shell.env[i]);
			found = 1;
		}
		else
		{
		ret[i] = g_shell.env[i + found];
		i++;
		}
	}
	i = 0;
	free(s);
	free(g_shell.env);
	g_shell.env = ret;
}

void	unset(t_cmd *cmd)
{
	int		i;
	char	*s;

	i = 0;
	while (cmd->args[i])
	{
		if (var_isvalid(cmd->args[i], 1))
		{
			s = find_var(cmd->args[i]);
			if (s)
			{
				del_var(ft_strjoin(cmd->args[i], "="));
				free(s);
			}
		}
		else
		{
			ft_putstr("unset: '");
			ft_putstr(cmd->args[i]);
			ft_putstr_nl("': not a valid identifier");
			g_shell.status = 1;
		}
		i++;
	}
}
