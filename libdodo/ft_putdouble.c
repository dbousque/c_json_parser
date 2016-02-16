/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdouble.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 13:28:39 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:18:57 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

char	*get_second_part(double nb)
{
	char	*res;
	int		i;

	if (!(res = (char*)malloc(sizeof(char) * 8)))
		return (NULL);
	res[7] = '\0';
	res[0] = '.';
	i = 1;
	nb -= ((long long)(nb + 0.000001));
	while (i < 7)
	{
		nb *= 10.0;
		res[i] = ((int)(nb + 0.000001)) + '0';
		nb -= (int)(nb + 0.000001);
		i++;
	}
	return (res);
}

int		ft_putdouble(double nb, char **str)
{
	char	*first_part;
	char	*second_part;

	ft_putlonglong((long long)nb, &first_part);
	if (nb < 0.0)
		nb = -nb;
	second_part = get_second_part(nb);
	*str = ft_strjoin(first_part, second_part);
	free(first_part);
	free(second_part);
	return (ft_strlen(*str));
}
