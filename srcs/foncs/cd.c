#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern t_shell	g_shell;

void	tmp1(void)
{
	int		error;
	char	*s;

	error = chdir((s = find_var("HOME")));
	if (s && s[0] != 0)
		free(s);
	if (error != 0)
	{
		s = strerror(errno);
		printf("%s\n", s);
	}
}

void	tmp2(t_cmd *cmd)
{
	int		error;
	char	*s;

	error = chdir(cmd->args[1]);
	if (error != 0)
	{
		s = strerror(errno);
		printf("%s\n", s);
	}
}

void	tmp3(t_cmd *cmd)
{
	int		error;
	char	*s;

	error = chdir(cmd->args[1]);
	if (error != 0)
	{
		s = strerror(errno);
		printf("%s\n", s);
	}
}

void	cd(t_cmd *cmd)
{
	if (!(cmd->args[1]) || !ft_strcmp(cmd->args[1], "~"))
		tmp1();
	else if (cmd->args[1][0] == '/')
		tmp2(cmd);
	else
		tmp3(cmd);
}
