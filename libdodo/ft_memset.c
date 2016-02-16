/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:01:32 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:52:52 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	val;
	int				i;

	val = (unsigned char)c;
	str = (unsigned char*)b;
	i = 0;
	while (i < (int)len)
	{
		str[i] = val;
		i++;
	}
	return (b);
}
