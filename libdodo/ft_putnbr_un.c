/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:17:48 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:17:51 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_putnbr_un(unsigned int n)
{
	int		length;

	if (n < 10)
	{
		ft_putchar(n + '0');
		return (1);
	}
	else
	{
		length = ft_putnbr_un(n / 10);
		ft_putchar(n % 10 + '0');
		return (length + 1);
	}
}
