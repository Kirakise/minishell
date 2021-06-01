#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <curses.h>
# include <term.h>

typedef struct s_shell
{
	char	**env;
	t_2list	*hist;
	int		fd_1;
	int		fd_0;
	int		tmp_fd_1;
	int		tmp_fd_0;
	int		fd_file;
	int		fd[2];
	pid_t	pidt;
	int		status;
	int		pipe0_open;
}		t_shell;

typedef struct s_redir
{
	int		type;
	char	*filename;
}				t_redir;
//	type == 0 : '>', type == 1 : '>>', type == 2 : '<'

typedef struct s_cmd
{
	char	*error;
	char	*exec_name;
	char	**args;
	int		pipe;
	int		pipe_out;
	t_redir	**redir;
}				t_cmd;

/*Fonctions*/
void		do_coms(int i, t_cmd **cmd, int fd_in, int fd_out);
int			do_exec(t_cmd *cmd);
void		do_redirect(t_cmd *cmd, int *fd_out, int *fd_in);
void		free_cmd(t_cmd **cmd);
void		parentproc(t_cmd **cmd, int i, int fd_in, int fd_out);
void		pwd(void);
void		envprint(int regime);
void		ft_echo(t_cmd *cmd);
void		cd(t_cmd *cmd);
void		export(t_cmd *cmd);
char		*get_name(char *s);
int			var_isvalid(char *str, int cmd_type);
void		unset(t_cmd *cmd);
void		add_var_exist(char *s);
void		add_var(char *s);
void		sh_exit(t_cmd *cmd);

/*Parser*/
t_cmd		**get_commands(char *s);
void		subst_quotes_vars(t_cmd *cmd);
/*Parser backend*/
char		*parse_input(char **input, char **err);
int			parse_command(char **s, t_cmd *cmd, t_list **arg_list);
int			parse_arguments(char **s, t_cmd *cmd, t_list **arg_list);
int			parse_redir_before(char **s, t_cmd *cmd, t_list **lst_redir);
int			parse_redir_pipe(char **s, t_cmd *cmd, t_list **lst_redir);
int			parse_str_chunk(char **input, char **res);

void		init_struct(int argc, char **argv);
char		**envcpy(char **line);
char		*find_var(char *s1);
char		*tmpread(void);
void		history_update(t_2list **hist, char *s);
char		*get_history_line(t_2list **lst, int dir, int *end);
void		history_free(t_2list **hist);
void		changeold(void);

/*termcaps*/
void		setc(struct termios *term);
void		setic(struct termios *term);
int			setinit(struct termios *term);
void		handlesigint(int a);

/*errors*/
void		ft_puterr(char *program_name, char *arg, int status);
void		malloc_err(void);
#endif
