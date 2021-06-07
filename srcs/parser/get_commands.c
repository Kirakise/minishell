#include "../../includes/minishell.h"

extern t_shell	g_shell;

static void	init_cmd_el(t_cmd *cmd)
{
	cmd->error = 0;
	cmd->pipe = 0;
	cmd->pipe_out = 0;
	cmd->exec_name = 0;
	cmd->args = 0;
	cmd->redir = 0;
}

static int	syntax_err(char *err)
{
	g_shell.status = 258;
	if (!err)
	{
		ft_putstr_nl("Syntax error");
		return (1);
	}
	ft_putstr("Syntax error near `");
	ft_putstr(err);
	ft_putstr("'\n");
	free(err);
	return (1);
}

int	str_to_commands(char *s, t_list **cmd_list)
{
	t_cmd	*cmd;
	t_list	*arg_list;
	t_list	*redir_list;

	while (*s)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			malloc_err();
		init_cmd_el(cmd);
		arg_list = 0;
		redir_list = 0;
		parse_redir_before(&s, cmd, &redir_list);
		if (!cmd->error)
			parse_command(&s, cmd, &arg_list);
		if (!cmd->error)
			parse_arguments(&s, cmd, &arg_list);
		if (!cmd->error)
			parse_redir_pipe(&s, cmd, &redir_list);
		if (cmd->error)
			return (syntax_err(cmd->error));
		cmd->args = (char **)lst_to_arr(arg_list);
		ft_lstadd_back(cmd_list, ft_lstnew(cmd));
	}
	return (0);
}

t_cmd	**get_commands(char *s)
{
	t_list	*cmd_list;
	t_cmd	**cmd_arr;

	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (0);
	cmd_list = 0;
	if (str_to_commands(s, &cmd_list) != 0)
		return (0);
	cmd_arr = (t_cmd **)lst_to_arr(cmd_list);
	return (cmd_arr);
}
