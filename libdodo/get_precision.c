/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_precision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:04:58 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:06:15 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void		get_precision(const char *fo, t_format *format, int *i, va_list ap)
{
	int		res;

	if (fo[*i] == '.' && fo[*i + 1] >= '0' && fo[*i + 1] <= '9')
	{
		res = ft_atoi(fo + *i + 1);
		*i += ft_intlen(res) + 1;
		format->precision = res;
	}
	else if (fo[*i] == '.' && fo[*i + 1] == '*')
	{
		(*i) += 2;
		format->precision = va_arg(ap, int);
	}
	else if (fo[*i] == '.')
	{
		(*i)++;
		format->precision = 0;
	}
	else
		format->precision = -1;
}
