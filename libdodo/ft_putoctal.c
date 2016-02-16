/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:17:27 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:17:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_putoctal(long long value, char **str)
{
	if ((*str = ft_ntoa_base(value, "01234567")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_putoctal_un(unsigned long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "01234567")))
		return (ft_strlen(*str));
	return (0);
}
