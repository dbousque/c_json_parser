/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 12:00:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/21 15:43:30 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_puthexa(unsigned long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "0123456789abcdef")))
		return (ft_strlen(*str));
	return (0);
}

int		ft_puthexa_maj(unsigned long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "0123456789ABCDEF")))
		return (ft_strlen(*str));
	return (0);
}
