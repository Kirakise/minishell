/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:21:18 by rgreater          #+#    #+#             */
/*   Updated: 2021/01/26 02:55:12 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		remain_initialize(char **remain)
{
	if (!*remain)
	{
		if (!(*remain = malloc(sizeof(char))))
			return (-1);
		*remain[0] = 0;
	}
	return (0);
}

int		fill_remain(char **remain, char *buf)
{
	char	*tmp;
	size_t	len_remain;
	size_t	len_buf;

	len_remain = ft_strlen(*remain);
	len_buf = ft_strlen(buf);
	if (!(tmp = malloc(sizeof(char) * (len_remain + len_buf + 1))))
		return (-1);
	ft_memmove(tmp, *remain, len_remain);
	ft_memmove(tmp + len_remain, buf, len_buf + 1);
	free(*remain);
	*remain = tmp;
	return (0);
}

int		fill_line(char **line, char *buf, int nl_index)
{
	buf[nl_index] = 0;
	if (!(*line = malloc(sizeof(char) * (nl_index + 1))))
		return (-1);
	ft_memmove(*line, buf, nl_index + 1);
	return (0);
}

int		read_buffer(int fd, char **remain)
{
	char		*buf;
	int			rd;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((rd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rd] = 0;
		if (fill_remain(remain, buf) == -1)
		{
			free(buf);
			return (-1);
		}
		if (find_nl(buf) >= 0)
			break ;
	}
	free(buf);
	return (rd);
}

int		get_next_line(int fd, char **line)
{
	static char *remain = 0;
	int			rd;
	int			nl_index;

	if (BUFFER_SIZE < 1 || line == NULL || remain_initialize(&remain) == -1)
		return (-1);
	rd = 1;
	while (rd > 0)
		if ((nl_index = find_nl(remain)) >= 0)
		{
			if (fill_line(line, remain, nl_index) == -1)
				return (terminate(&remain, -1));
			if (remain_update(&remain, nl_index + 1) == -1)
				return (terminate(&remain, -1));
			return (1);
		}
		else if ((rd = read_buffer(fd, &remain)) == -1)
			return (terminate(&remain, -1));
	if (fill_line(line, remain, ft_strlen(remain)) == -1)
		return (terminate(&remain, -1));
	if (*remain)
		return (terminate(&remain, 1));
	return (terminate(&remain, 0));
}
