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

/* структура с командами и аргументами
** первое поле можно будет выкинуть
** в exec_name имя команды, в args - аргументы
** pipe может быть 0 или 1
** 1 означает что в конце аргументов есть '|' - в саму строку аргументов этот слеш не включаю
** редиректы и все более-менее умное пока не обрабатывал
*/

typedef struct s_cmd
{
	int		type;
	char	*error;
	char	*exec_name;
	char	**args;
	int		pipe;
	int		pipe_out;
	int		redirect; //0 == no redirect; 1 == '>'; 2 == '>>'
	char	*redirect_filename;
}				t_cmd;

/*Fonctions*/
void		pwd(void);
void		envprint(void);
void		ft_echo(t_cmd *cmd);
void		do_coms(int i, t_cmd **cmd, int fd_in, int fd_out);
int			do_exec(t_cmd *cmd);
void		cd(t_cmd *cmd);
void		free_cmd(t_cmd **cmd);
void		parentproc(t_cmd **cmd, int i, int fd_in, int fd_out);
void		export(t_cmd *cmd);
char		*get_name(char *s);
void		unset(t_cmd *cmd);

/*Parser*/
t_cmd		**get_commands(char *s);
void		subst_vars(char **str);
void		parsevars(char **s);

/*Utils*/
int			init_struct(void);
char		**envcpy(char **line);
char		*find_var(char *s1);
char		*tmpread(void);
void		history_update(t_2list **hist, char *s);
char		*get_history_line(t_2list **lst, int dir, int *end);
void		history_free(t_2list **hist);

/*termcaps*/
void		setc(struct termios *term);
void		setic(struct termios *term);
int			setinit(struct termios *term);
void		handlesigint(int a);
#endif
