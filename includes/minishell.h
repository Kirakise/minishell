#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct	s_shell{
	char	**env;
	int	fd_1;
	int	fd_0;
	int	tmp_fd_1;
	int	tmp_fd_0;
}		t_shell;

//это не факт что пригодится, но пускай пока будет
enum cmd_type
{
	c_echo = 1,
	c_cd = 2,
	c_pwd = 3,
	c_export = 4,
	c_unset = 5,
	c_env = 6,
	c_exit = 7,
	c_exec = 8
};

/* структура с командами и аргументами
** первое поле можно будет выкинуть
** в exec_name имя команды, в args - аргументы
** pipe может быть 0 или 1
** 1 означает что в конце аргументов есть '|' - в саму строку аргументов этот слеш не включаю
** редиректы и все более-менее умное пока не обрабатывал
*/

typedef struct	s_cmd
{
	int		type;
	char	*exec_name;
	char	*args;
	int		pipe;
}				t_cmd;

/*Fonctions*/
void		pwd(void);
void		envprint(void);
void		echo(char *s);

/*Parser*/
t_cmd		**get_commands(char *s);

/*Utils*/
int 		init_struct(void);
char		**envcpy(char **line);

#endif
