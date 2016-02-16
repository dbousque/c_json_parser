/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_n_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:06:45 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:08:23 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int			get_size(char c)
{
	if (c == HH)
		return (sizeof(char));
	if (c == H)
		return (sizeof(short));
	if (c == L)
		return (sizeof(long));
	if (c == LL)
		return (sizeof(long long));
	if (c == Z)
		return (sizeof(size_t));
	if (c == J)
		return (sizeof(long long));
	return (0);
}

void		update_length(t_format *format_var, char new_length)
{
	int		sizeof_current;
	int		sizeof_new;

	sizeof_current = get_size(format_var->length);
	sizeof_new = get_size(new_length);
	if (sizeof_new > sizeof_current)
		format_var->length = new_length;
}

void		get_length(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == 'l' && format[*i + 1] == 'l')
		update_length(format_var, LL);
	else if (format[*i] == 'l')
		update_length(format_var, L);
	else if (format[*i] == 'h' && format[*i + 1] == 'h')
		update_length(format_var, HH);
	else if (format[*i] == 'h')
		update_length(format_var, H);
	else if (format[*i] == 'j')
		update_length(format_var, J);
	else if (format[*i] == 'z')
		update_length(format_var, Z);
	else
		format_var->length = NO_FLAG;
	if (format_var->length == HH || format_var->length == LL)
		(*i) += 2;
	else if (format_var->length != NO_FLAG)
		(*i)++;
}

void		get_width(const char *format, t_format *formatv, int *i, va_list ap)
{
	int		res;

	if (format[*i] >= '1' && format[*i] <= '9')
	{
		res = ft_atoi(format + *i);
		*i += ft_intlen(res);
		formatv->width = res;
	}
	else if (format[*i] == '*')
	{
		(*i)++;
		formatv->width = va_arg(ap, int);
		if (formatv->width < 0)
		{
			formatv->minus_flag = 1;
			formatv->width = -formatv->width;
		}
	}
}

void		get_star_width(const char *fo, t_format *format, int *i, va_list ap)
{
	if (fo[*i] == '*')
	{
		(*i)++;
		format->width = va_arg(ap, int);
		if (format->width < 0)
		{
			format->minus_flag = 1;
			format->width = -format->width;
		}
	}
}
