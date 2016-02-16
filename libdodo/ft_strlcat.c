/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:16:17 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:57:33 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	int		j;
	int		length;

	i = 0;
	j = 0;
	while (dst[i] && i < (int)size)
		i++;
	length = i;
	if (length == (int)size)
		return (length + ft_strlen(src));
	while (src[j] && j + i + 1 < (int)size)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (length + ft_strlen(src));
}
