/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/22 18:58:28 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:15:25 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		arg_putaddr(va_list ap, char flag, char **str, t_format *format_var)
{
	void	*res;
	int		length;

	(void)flag;
	res = va_arg(ap, void*);
	format_var->unsigned_val = 1;
	length = ft_putaddr(res, 1, str, format_var);
	return (length);
}

int		arg_putoctal(va_list ap, char flag, char **str, t_format *format_var)
{
	unsigned long long	res;
	int					length;

	if (flag == L)
		res = va_arg(ap, unsigned long);
	else if (flag == LL)
		res = va_arg(ap, unsigned long long);
	else if (flag == H)
		res = (unsigned short)va_arg(ap, unsigned int);
	else if (flag == HH)
		res = (unsigned char)va_arg(ap, unsigned int);
	else if (flag == J)
		res = va_arg(ap, unsigned long long);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	format_var->u_value = res;
	format_var->unsigned_val = 1;
	length = ft_putoctal_un(res, str);
	return (length);
}

int		arg_putoctal_long(va_list ap, char flag, char **str, t_format *format)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	format->u_value = res;
	format->unsigned_val = 1;
	length = ft_putoctal_un(res, str);
	return (length);
}

int		arg_putbinary(va_list ap, char flag, char **str, t_format *format_var)
{
	long long	res;
	int			length;

	if (flag == L)
		res = va_arg(ap, long);
	else if (flag == LL)
		res = va_arg(ap, long long);
	else if (flag == H)
		res = (short)va_arg(ap, int);
	else if (flag == HH)
		res = (char)va_arg(ap, int);
	else if (flag == J)
		res = va_arg(ap, long long);
	else if (flag == Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, int);
	format_var->value = res;
	length = ft_putbinary(res, str);
	return (length);
}
