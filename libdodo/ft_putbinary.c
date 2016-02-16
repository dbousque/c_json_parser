/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbinary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:19:18 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:19:21 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_putbinary(long long value, char **str)
{
	if ((*str = ft_ntoa_base_un(value, "01")))
		return (ft_strlen(*str));
	return (0);
}
