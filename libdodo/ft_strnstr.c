/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:30:33 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:11:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int		s1_i;
	int		s2_i;
	int		ori_i;

	if (*s2 == '\0')
		return ((char*)s1);
	s1_i = 0;
	while (s1[s1_i] && s1_i < (int)n)
	{
		ori_i = s1_i;
		s2_i = 0;
		while (s1[s1_i] == s2[s2_i] && s1[s1_i] && s1_i < (int)n)
		{
			s1_i++;
			s2_i++;
		}
		if (s2[s2_i] == '\0')
			return ((char*)s1 + ori_i);
		s1_i = ori_i;
		s1_i++;
	}
	return (NULL);
}
