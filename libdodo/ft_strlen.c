/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:32:36 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:56:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

size_t	ft_strlen_bis(const char *s)
{
	char	*s_start;

	s_start = (char*)s;
	while (*s)
		s++;
	return ((size_t)(s - s_start));
}

size_t	ft_strlen_bis2(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}