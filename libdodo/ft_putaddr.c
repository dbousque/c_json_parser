/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:19:39 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:19:45 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_putaddr(void *addr, char long_long, char **str, t_format *format)
{
	long long	value;

	value = (long_long ? (long long)addr : (long)addr);
	format->u_value = value;
	*str = ft_ntoa_base(value, "0123456789abcdef");
	if (!(*str))
		*str = ft_strdup("0");
	return (ft_strlen(*str));
}
