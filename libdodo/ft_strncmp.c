/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:20:30 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:59:02 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if ((int)n == 0)
		return (0);
	return ((*s1 == *s2 && *s1 && n > 1) ?
			ft_strncmp(s1 + 1, s2 + 1, n - 1)
			: (unsigned char)*s1 - (unsigned char)*s2);
}
