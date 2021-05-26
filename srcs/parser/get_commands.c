#include "../../includes/minishell.h"

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
	if (!err)
	{
		ft_putstr_nl("Syntax error");
		return (1);
	}
	ft_putstr("Syntax error near '");
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
		cmd = malloc(sizeof(t_cmd));//malloc
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

/*static void	test_print(t_cmd **cmd_arr)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_arr[i])
	{
		printf("\n%-6s %s\n", "cmd   :   ", cmd_arr[i]->exec_name);
		j = 0;
		while (cmd_arr[i]->args[j])
		{
			printf("arg[%d]:    %s|\n", j, cmd_arr[i]->args[j]);
			j++;
		}
		printf("pipe  :    %d\n", cmd_arr[i]->pipe);
		j = 0;
		while (cmd_arr[i]->redir && cmd_arr[i]->redir[j])
		{
			printf("redir : ");
			if (cmd_arr[i]->redir[j]->type == 0)
				printf(" > ");
			else if (cmd_arr[i]->redir[j]->type == 1)
				printf(">> ");
			else
				printf(" < ");
			printf("%s|\n", cmd_arr[i]->redir[j]->filename);
			j++;
		}
		i++;
	}
}*/

t_cmd	**get_commands(char *s)
{
	t_list	*cmd_list;
	t_cmd	**cmd_arr;

	if (!s || !*s)
		return (0);
	cmd_list = 0;
	if (str_to_commands(s, &cmd_list) != 0)
		return (0);
	cmd_arr = (t_cmd **)lst_to_arr(cmd_list);
//	test_print(cmd_arr);
/*	int i = 0;
	while (cmd_arr[i])
		subst_quotes_vars(cmd_arr[i++]);
	test_print(cmd_arr);*/
	return (cmd_arr);
}
