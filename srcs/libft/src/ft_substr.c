/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaraway <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:09:44 by rcaraway          #+#    #+#             */
/*   Updated: 2020/11/01 19:10:36 by rcaraway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char *ret;
	char *tmp;

	if (!s)
		return (0);
	ret = ft_calloc(len + 1, 1);
	if (ret == 0)
		return (0);
	if (start >= ft_strlen(s))
		return (ret);
	tmp = ret;
	s += start;
	while (*s && len--)
		*ret++ = *s++;
	*ret = 0;
	return (tmp);
}
