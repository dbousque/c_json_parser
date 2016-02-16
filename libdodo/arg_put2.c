/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_put2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 17:12:42 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:13:28 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		arg_putnbr(va_list ap, char flag, char **str, t_format *format_var)
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
	if (res < 0)
		format_var->neg_val = 1;
	format_var->value = res;
	length = ft_putlonglong(res, str);
	return (length);
}

int		arg_putnbr_long(va_list ap, char flag, char **str, t_format *format_var)
{
	long long	res;
	int			length;

	if (flag == L || flag == LL)
		res = va_arg(ap, long long);
	else
		res = va_arg(ap, long);
	if (res < 0)
		format_var->neg_val = 1;
	format_var->value = res;
	length = ft_putlonglong(res, str);
	return (length);
}

int		arg_putfloat(va_list ap, char flag, char **str, t_format *format_var)
{
	double	res;
	int		length;

	(void)flag;
	res = va_arg(ap, double);
	if (res < 0)
		format_var->neg_val = 1;
	format_var->value = (long long)res;
	length = ft_putdouble(res, str);
	return (length);
}

int		arg_putnbr_un(va_list ap, char flag, char **str, t_format *format_var)
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
	format_var->unsigned_val = 1;
	format_var->u_value = res;
	length = ft_putlonglong_un(res, str);
	return (length);
}

int		arg_putnbr_un_long(va_list ap, char flag, char **str, t_format *format)
{
	unsigned long long	res;
	int					length;

	if (flag == L || flag == LL)
		res = va_arg(ap, unsigned long long);
	else
		res = va_arg(ap, unsigned long);
	format->unsigned_val = 1;
	format->u_value = res;
	length = ft_putlonglong_un(res, str);
	return (length);
}
