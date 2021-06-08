#include "../../includes/minishell.h"

extern t_shell	g_shell;

static int	update_env(char *str)
{
	char	*s;
	char	*s2;

	if (!var_isvalid(str, 0))
		return (export_puterr(str));
	s = get_name(str);
	if (!s)
		return (0);
	s2 = find_var(s);
	free(s);
	if (s2)
	{
		add_var_exist(str);
		free(s2);
	}
	else
		add_var(str);
	return (0);
}

void	export(t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	while (cmd->args[i])
	{
		update_env(cmd->args[i]);
		i++;
	}
	status = g_shell.status;
	if (!cmd->args[1] && !fork())
		envprint(1);
	wait(&g_shell.status);
	wait(&g_shell.status);
	if (status && g_shell.status == 0)
		g_shell.status = status;
}
