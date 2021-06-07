#include "../../includes/minishell.h"

extern t_shell	g_shell;

static int	get_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static void	handle_err(char **name)
{
	ft_putstr("minishell: ");
	ft_putstr(*name);
	ft_putstr_nl(": ambiguous redirect");
	free(*name);
	*name = ft_strdup("");
	g_shell.status = 1;
}

static int	check_for_variables(char *arg, char *redir)
{
	char	*name;
	char	*res;

	if (redir[0] == '$' && !ft_strncmp(arg, (redir + 1), get_length(arg)))
	{
		name = ft_substr(arg, 0, get_length(arg));
		if (!name)
			malloc_err();
		res = find_var(name);
		free(name);
		if (!res)
		{
			free(res);
			return (1);
		}
	}
	return (0);
}

void	check_export_redir(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->redir[j])
		{
			if (check_for_variables(cmd->args[i], cmd->redir[j]->filename))
			{
				handle_err(&cmd->redir[j]->filename);
				return ;
			}
			j++;
		}
		i++;
	}
}
