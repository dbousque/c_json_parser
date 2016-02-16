/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:54:11 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:30:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		handle_new_format(const char *format, int *i, va_list ap, t_format *fo)
{
	int		length;

	length = 0;
	fo = new_format();
	if (parse_format(format, fo, i, ap) != -1)
		length = print_format(fo, ap);
	else
		(*i)--;
	if (fo)
		free_format(fo);
	return (length);
}

void	std_char(const char *format, int *i, int *length)
{
	if (format[*i] == '%')
		(*i)++;
	if (format[*i])
	{
		ft_putchar(format[*i]);
		(*length)++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	int			length;
	t_format	*format_var;

	length = 0;
	if (format)
		va_start(ap, format);
	i = 0;
	format_var = NULL;
	while (format && format[i])
	{
		if (format[i] == '{')
			ft_change_color_if_asked(format, &i);
		if (format[i] == '%' && format[i + 1] != '%')
			length += handle_new_format(format, &i, ap, format_var);
		else
			std_char(format, &i, &length);
		if (format[i])
			i++;
	}
	return (length);
}
