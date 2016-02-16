/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 11:59:09 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:05:55 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			if (n > -10)
				ft_putchar_fd(-n + '0', fd);
			else
			{
				ft_putnbr_fd(-(n / 10), fd);
				ft_putchar_fd(-(n % 10) + '0', fd);
			}
		}
		else
		{
			if (n < 10)
				ft_putchar_fd(n + '0', fd);
			else
			{
				ft_putnbr_fd(n / 10, fd);
				ft_putchar_fd(n % 10 + '0', fd);
			}
		}
	}
}
