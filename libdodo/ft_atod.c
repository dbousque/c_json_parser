/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:49:34 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 11:59:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

static int	ft_is_valid(char c)
{
	if (c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

double	ft_atod(const char *str)
{
	double	res;
	int		i;
	char	signe;
	long	neg;

	i = 0;
	res = 0.0;
	signe = 1;
	while (ft_is_valid(str[i]) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	i++;
	neg = 10;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += (((double)(str[i] - '0')) / neg);
		neg *= 10;
		i++;
	}
	if (signe == -1)
		res = -res;
	return (res);
}