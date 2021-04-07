#include "minishell.h"

void	ft_bzero2(char *s)
{
	int i;

	i = 0;
	while (i <= BUFFER_SIZE)
		s[i++] = 0;
}

int		get_next_line(int fd, char **line)
{
	static t_str	arr[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0))
		return (-1);
	*line = malloc(1);
	**line = 0;
	return (ft_getline(fd, &(arr[fd]), line, 0));
}
