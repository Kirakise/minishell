/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgreater <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:19:52 by rgreater          #+#    #+#             */
/*   Updated: 2021/03/05 16:35:06 by rgreater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16384
# endif
# include "libft.h"

int		find_nl(char *str);
int		remain_update(char **str, int index);
int		terminate(char **remain, int ret_val);

#endif
