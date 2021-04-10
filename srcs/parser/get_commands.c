#include <stdio.h>
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

//  вот эту функцию можно применить в той части программы, которая выполняет команды,
//  заменив return на вызов соответствующих функций

static int	get_typeof_cmd(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (c_echo);
	else if (!ft_strcmp(str, "cd"))
		return (c_cd);
	else if (!ft_strcmp(str, "pwd"))
		return (c_pwd);
	else if (!ft_strcmp(str, "export"))
		return (c_export);
	else if (!ft_strcmp(str, "unset"))
		return (c_unset);
	else if (!ft_strcmp(str, "env"))
		return (c_env);
	else if (!ft_strcmp(str, "exit"))
		return (c_exit);
	return (c_exec);
}

static void	handle_quotes(int *val)
{
	int quotes;

	quotes = *val;
	if (quotes == 0)
		quotes++;
	else
		quotes--;
	*val = quotes;
}

static char *parse_input(char **input, int *end, char **err)
{
	int		quotes[2];
	char	*s;
	char	*str;
	int		i;

	s = *input;
	while (ft_isspace(*s))
		s++;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		exit(1); // malloc protection....
	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (*s && !*end && (!ft_isspace(*s) || quotes[0] || quotes[1]))
	{
		if (*s == '\'' && !quotes[1])
			handle_quotes(&quotes[0]);
		else if (*s == '"' && !quotes[0])
			handle_quotes(&quotes[1]);
		else if (*s == ';' && !quotes[0] && !quotes[1])
			*end = 1;
		else
		{
			str[i] = *s;
			i++;
		}
		s++;
	}
	str[i] = 0;
	*input = s;
	if (quotes[0])
		*err = "\'";
	if (quotes[1])
		*err = "\"";
	if (*end && *s == ';')
		*err = ";;";
	return (str);
}

static void	**lst_to_arr(t_list *lst, void **arr, int data_type)
{
	int		size;
	int		i;
	t_list	*lst_tmp;

	lst_tmp = lst;
	size = ft_lst_getsize(lst);
	arr = malloc(sizeof(t_list) * size + 1);
	if (!arr)
		exit(1);//malloc
	i = 0;
	while (lst)
	{
		if (data_type == 0)
			arr[i] = (char *)lst->content;
		else
			arr[i] = (t_cmd *)lst->content;
		i++;
		lst = lst->next;
	}
	arr[i] = (char*)0;//0;
	ft_lstdestroy(&lst_tmp);
	return (arr);
}

static void	init_cmd_el(t_cmd *cmd, int *end)
{
	cmd->error = 0;
	cmd->pipe = 0;
	cmd->pipe_out = 0;
	cmd->redirect = 0;
	*end = 0;
}

static void	check_pipe_redirect(char *str, t_cmd *cmd, int *end)
{
	int ret;

	ret = 1;
	if (!ft_strcmp(str, "|"))
		cmd->pipe = 1;
	else if (!ft_strcmp(str, ">"))
		cmd->redirect = 1;
	else if (!ft_strcmp(str, ">>"))
		cmd->redirect = 2;
	else
		ret = 0;
	if (ret)
	{
		*end = 1;
		free(str);
	}
}

t_cmd		**get_commands(char *s)
{
	char	*str;
	int		end;
	t_cmd	*cmd;
	t_list	*cmd_list;
	t_list	*arg_list;

//	printf("\n%-8s%s\n", "in: ", s);//
	cmd_list = 0;
	while (*s)
	{
		arg_list = 0;
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			exit(1);//malloc
		init_cmd_el(cmd, &end);
		str = parse_input(&s, &end, &cmd->error);
		if (cmd->error)
		{
			printf("Syntax error near %s\n", cmd->error);
			exit(1);
		}
		cmd->type = get_typeof_cmd(str);
		cmd->exec_name = ft_strdup(str);
		if (!cmd->exec_name)
			exit(1);//malloc
		free(str);
		str = ft_strdup(cmd->exec_name);
		if (!str)
			exit(1);//malloc
		ft_lstadd_back(&arg_list, ft_lstnew(str));
		while (*s && !end)
		{
			str = parse_input(&s, &end, &cmd->error);
			if (cmd->error)
			{
				printf("Syntax error near %s\n", cmd->error);
				exit(1);
			}
			check_pipe_redirect(str, cmd, &end);
			if (!end)
				ft_lstadd_back(&arg_list, ft_lstnew(str));
		}
		cmd->args = (char **)lst_to_arr(arg_list, (void **)cmd->args, 0);
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	}

	t_cmd	**cmd_arr;

	cmd_arr = 0;
	cmd_arr = (t_cmd **)lst_to_arr(cmd_list, (void **)cmd_arr, 1);

/*
	int i = 0;
	int j = 0;
	while (cmd_arr[i])
	{
		printf("%-6s%d %s\n", "cmd: ", cmd_arr[i]->type, cmd_arr[i]->exec_name);
		j = 0;
		while (cmd_arr[i]->args[j])
		{
			printf("arg[%d]: %s\n", j, cmd_arr[i]->args[j]);
			j++;
		}
		printf("pipe: %d\n", cmd_arr[i]->pipe);
		i++;
	}
*/
	return (cmd_arr);
}
