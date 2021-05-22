#include "../../includes/minishell.h"

static void	check_syntax(char **s, char **err)
{
	char	*str;

	str = *s;
	str++;
	if (*str == **s)
	{
		*(str + 1) = 0;
		*err = ft_strdup(str - 1);
		return ;
	}
	while (ft_isspace(*str))
		str++;
	if (!*str && **s != ';')
	{
		*err = ft_strdup(*s);
		return ;
	}
	*s = str;
}

static void	parse_redirect(char **s, char **err, t_list **lst, int type)
{
	t_redir	*el;

	el = malloc(sizeof(t_redir));//malloc
	if (!ft_strncmp(*s, ">>", 2))
		*s += 1;
	el->type = type;
	check_syntax(s, err);
	if (*err)
		return ;
	el->filename = parse_input(s, err);//malloc
	if (el->filename && *el->filename)
		ft_lstadd_back(lst, ft_lstnew(el));
	else
	{
		if (el->filename)
			free(el->filename);
		free(el);
		*err = ft_strdup(*s);
	}
}

int	parse_redir_pipe(char **s, t_cmd *cmd)
{
	t_list	*lst_redir;

	lst_redir = 0;
	while (**s && !ft_strchr(**s, ";|") && !cmd->error)
	{
		if (**s == '<')
			parse_redirect(s, &cmd->error, &lst_redir, 2);
		else if (!ft_strncmp(*s, ">>", 2))
			parse_redirect(s, &cmd->error, &lst_redir, 1);
		else if (**s == '>')
			parse_redirect(s, &cmd->error, &lst_redir, 0);
	}
	if (!cmd->error && lst_redir)
		cmd->redir = (t_redir **)lst_to_arr(lst_redir);
	if (!cmd->error && **s == '|')
	{
		check_syntax(s, &cmd->error);
		cmd->pipe = 1;
	}
	if (!cmd->error && **s == ';')
		check_syntax(s, &cmd->error);
	if (cmd->error)
		return (1);
	return (0);
}
