#include "../../includes/minishell.h"

static void	check_syntax(char **s, t_err *err)
{
	char	*str;

	str = *s;
	str++;
	if (*str == **s || ft_strchr(*str, "<>|;"))
	{
		*(str + 1) = 0;
		err->val = ft_strdup(str - 1);
		if (!err->val)
			malloc_err();
		return ;
	}
	while (ft_isspace(*str))
		str++;
	if (!*str && **s != ';')
	{
		err->val = ft_strdup(*s);
		if (!err->val)
			malloc_err();
		return ;
	}
	*s = str;
}

static void	free_el(t_redir *el)
{
	if (el->filename)
		free(el->filename);
	free(el);
}

static void	parse_redirect(char **s, t_err *err, t_list **lst, int type)
{
	t_redir	*el;

	if (!ft_strncmp(*s, ">>", 2))
		*s += 1;
	check_syntax(s, err);
	if (err->val)
		return ;
	el = malloc(sizeof(t_redir));
	if (!el)
		malloc_err();
	el->type = type;
	el->filename = parse_input(s, err);
	if (!err->val && el->filename && *el->filename)
	{
		ft_lstadd_back(lst, ft_lstnew(el));
		return ;
	}
	free_el(el);
	if (err->val)
		return ;
	err->val = ft_strdup(*s);
	if (!err->val)
		malloc_err();
}

int	parse_redir_pipe(char **s, t_cmd *cmd, t_list **lst_redir)
{
	while (**s && !ft_strchr(**s, ";|") && !cmd->error.val)
	{
		if (**s == '<')
			parse_redirect(s, &cmd->error, lst_redir, 2);
		else if (!ft_strncmp(*s, ">>", 2))
			parse_redirect(s, &cmd->error, lst_redir, 1);
		else if (**s == '>')
			parse_redirect(s, &cmd->error, lst_redir, 0);
	}
	if (*lst_redir)
	{
		cmd->redir = (t_redir **)lst_to_arr(*lst_redir);
		if (!cmd->redir)
			malloc_err();
	}
	if (!cmd->error.val && **s == '|')
	{
		check_syntax(s, &cmd->error);
		cmd->pipe = 1;
	}
	if (!cmd->error.val && **s == ';')
		check_syntax(s, &cmd->error);
	if (cmd->error.val)
		return (1);
	return (0);
}

int	parse_redir_before(char **s, t_cmd *cmd, t_list **lst_redir)
{
	while (ft_isspace(**s))
		*s += 1;
	while ((**s == '<' || **s == '>') && !cmd->error.val)
	{
		while (ft_isspace(**s))
			*s += 1;
		if (**s == '<')
			parse_redirect(s, &cmd->error, lst_redir, 2);
		else if (!ft_strncmp(*s, ">>", 2))
			parse_redirect(s, &cmd->error, lst_redir, 1);
		else if (**s == '>')
			parse_redirect(s, &cmd->error, lst_redir, 0);
		while (ft_isspace(**s))
			*s += 1;
	}
	if (cmd->error.val)
	{
		ft_lstdestroy(lst_redir, 1);
		return (1);
	}
	return (0);
}
