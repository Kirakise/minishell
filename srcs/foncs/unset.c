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
		if (!ft_strncmp(s, g_shell.env[i], ft_strlen(s)))
		{
			found = 1;
			free(g_shell.env[i]);
		}
		ret[i] = g_shell.env[i + found];
		i++;
	}
	i = 0;
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
		s = find_var(cmd->args[i]);
		if (s[0])
			del_var(cmd->args[i]);
		free(s);
		i++;
	}
}
