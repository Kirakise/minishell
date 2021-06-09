#include "../../includes/minishell.h"

extern t_shell	g_shell;

static void	init_cmd_el(t_cmd *cmd, t_list **arg_list, t_list **redir_list)
{
	cmd->error.type = 0;
	cmd->error.val = 0;
	cmd->pipe = 0;
	cmd->pipe_out = 0;
	cmd->exec_name = 0;
	cmd->args = 0;
	cmd->redir = 0;
	*arg_list = 0;
	*redir_list = 0;
}

static void	free_cmd_el(t_cmd *cmd)
{
	int	i;

	safe_free(cmd->exec_name);
	i = 0;
	while (cmd->args && cmd->args[i])
		safe_free(cmd->args[i++]);
	safe_free(cmd->args);
	i = 0;
	while (cmd->redir && cmd->redir[i])
		safe_free(cmd->redir[i++]);
	safe_free(cmd->redir);
	safe_free(cmd->error.val);
	free(cmd);
}

static int	syntax_err(t_err err)
{
	g_shell.status = 258;
	ft_putstr("minishell: ");
	if (err.type == 1)
	{
		ft_putstr("syntax error near `");
		ft_putstr(err.val);
		ft_putstr_nl("'. Multiline commands are not supported");
	}
	else
	{
		ft_putstr("syntax error near unexpected token `");
		ft_putstr(err.val);
		ft_putstr("'\n");
	}
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
		init_cmd_el(cmd, &arg_list, &redir_list);
		parse_redir_before(&s, cmd, &redir_list);
		if (!cmd->error.val)
			parse_command(&s, cmd, &arg_list);
		if (!cmd->error.val)
			parse_arguments(&s, cmd, &arg_list);
		if (!cmd->error.val)
			parse_redir_pipe(&s, cmd, &redir_list);
		cmd->args = (char **)lst_to_arr(arg_list);
		ft_lstadd_back(cmd_list, ft_lstnew(cmd));
		if (cmd->error.val)
			return (syntax_err(cmd->error));
	}
	return (0);
}

t_cmd	**get_commands(char *s)
{
	int		err;
	int		i;
	t_list	*cmd_list;
	t_cmd	**cmd_arr;

	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (0);
	cmd_list = 0;
	err = str_to_commands(s, &cmd_list);
	cmd_arr = (t_cmd **)lst_to_arr(cmd_list);
	if (err)
	{
		i = 0;
		while (cmd_arr && cmd_arr[i])
			free_cmd_el(cmd_arr[i++]);
		free(cmd_arr);
		cmd_arr = 0;
	}
	return (cmd_arr);
}
