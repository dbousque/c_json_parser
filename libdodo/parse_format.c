/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:08:57 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:15:29 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void		get_start_flags(const char *format, t_format *format_var, int *i)
{
	while (format[*i] == '-')
		get_minus_flag(format, format_var, i);
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	while (format[*i] == ' ')
		get_space_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
	while (format[*i] == '#')
		get_sharp_flag(format, format_var, i);
	while (format[*i] == '-')
		get_minus_flag(format, format_var, i);
	while (format[*i] == '#')
		get_sharp_flag(format, format_var, i);
	while (format[*i] == '0')
		get_zero_flag(format, format_var, i);
	while (format[*i] == '+')
		get_plus_flag(format, format_var, i);
}

void		get_following_flags(const char *f, t_format *fo, int *i, va_list ap)
{
	if (fo->minus_flag == 0)
	{
		while (f[*i] == '-')
			get_minus_flag(f, fo, i);
	}
	if (fo->sharp_flag == 0)
	{
		while (f[*i] == '#')
			get_sharp_flag(f, fo, i);
	}
	while (f[*i] == '0')
		get_zero_flag(f, fo, i);
	while (f[*i] == ' ')
		get_space_flag(f, fo, i);
	get_width(f, fo, i, ap);
	while (f[*i] == '*')
		get_star_width(f, fo, i, ap);
}

void		get_prec_n_length(const char *f, t_format *fo, int *i, va_list ap)
{
	while (f[*i] == '.')
		get_precision(f, fo, i, ap);
	while (f[*i] == 'h' || f[*i] == 'l' || f[*i] == 'j' || f[*i] == 'z')
		get_length(f, fo, i);
	if (fo->precision == -1)
	{
		while (f[*i] == '.')
			get_precision(f, fo, i, ap);
	}
	get_width(f, fo, i, ap);
}

void		get_end_flags(const char *f, t_format *fo, int *i, va_list ap)
{
	while (f[*i] == ' ')
		get_space_flag(f, fo, i);
	while (f[*i] == '+')
		get_plus_flag(f, fo, i);
	while (f[*i] == '#')
		get_sharp_flag(f, fo, i);
	while (f[*i] == '0')
		get_zero_flag(f, fo, i);
	while (f[*i] == '+')
		get_plus_flag(f, fo, i);
	get_width(f, fo, i, ap);
}

int			parse_format(const char *f, t_format *fo, int *i, va_list ap)
{
	(*i)++;
	get_start_flags(f, fo, i);
	get_following_flags(f, fo, i, ap);
	get_width(f, fo, i, ap);
	get_prec_n_length(f, fo, i, ap);
	get_end_flags(f, fo, i, ap);
	while (invalid_end(f[*i]))
		(*i)++;
	if (!is_valid_specifier(f[*i]) && !is_other_maj(f[*i]))
		return (-1);
	fo->specifier = f[*i];
	if (fo->width > fo->precision && fo->precision > -1
		&& !bad_specifier(fo->specifier))
		fo->char_to_fill = ' ';
	return (0);
}
