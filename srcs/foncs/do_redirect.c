#include "../../includes/minishell.h"

extern t_shell	g_shell;

static void	open_files(t_redir *redir, int pipe, int *fd_out, int *fd_in)
{
	int			fd;
	static int	err = 0;

	if (redir->type == 0 || redir->type == 1)
	{
		if (pipe && write(*fd_out, "\0", 1))
			close(*fd_out);
		if (redir->type == 0)
			*fd_out = open(redir->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else
			*fd_out = open(redir->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0664);
		return ;
	}
	fd = open(redir->filename, O_RDONLY);
	dup2(fd, *fd_in);
	if (fd < 0 && !err)
	{
		ft_putstr(redir->filename);
		ft_putstr_nl(": No such file or directory");
		err = 1;
		g_shell.status = 1;
	}
}

void	do_redirect(t_cmd *cmd, int *fd_out, int *fd_in)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (cmd->redir[i])
	{
		open_files(cmd->redir[i], cmd->pipe, fd_out, fd_in);
		i++;
	}	
}
