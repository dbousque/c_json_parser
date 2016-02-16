/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 13:39:26 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/21 15:41:37 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_putlong(long value, char **str)
{
	if ((*str = ft_ntoa_base(value, "0123456789")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_putlong_un(unsigned long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "0123456789")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_putlonglong(long long value, char **str)
{
	if ((*str = ft_ntoa_base(value, "0123456789")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_putlonglong_un(unsigned long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "0123456789")))
		return (ft_strlen(*str));
	return (0);
}
