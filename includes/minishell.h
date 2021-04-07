#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct	s_shell{
	char	**env;
	int	fd_1;
	int	fd_0;
	int	tmp_fd_1;
	int	tmp_fd_0;
}		t_shell;


/*Utils*/
int 		init_struct(void);
char		**envcpy(char **line);
char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);


/*Get_next_line*/
typedef	struct	s_str{
	int	fd;
	int	pos;
	char	buf[BUFFER_SIZE + 1];
}		t_str;
int		get_next_line(int fd, char **line);
void		ft_bzero(char **s);
int		ft_strlen(char *s);
void		ft_strjoin(char **s1, char **s2);
int		ft_getline(int fd, t_str *str, char **line, int i);
void		ft_bzero2(char *s);
#endif
