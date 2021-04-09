/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:39:50 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/05 16:32:12 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		find_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		remain_update(char **str, int index)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(*str + index) + 1;
	if (!(tmp = malloc(sizeof(char) * len)))
		return (-1);
	ft_memmove(tmp, *str + index, len);
	free(*str);
	*str = tmp;
	return (0);
}

int		terminate(char **remain, int ret_val)
{
	free(*remain);
	*remain = 0;
	return (ret_val);
}
