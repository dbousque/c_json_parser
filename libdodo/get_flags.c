/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 13:29:04 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 13:29:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void		get_zero_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '0')
	{
		format_var->char_to_fill = '0';
		(*i)++;
	}
}

void		get_minus_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '-')
	{
		format_var->minus_flag = 1;
		(*i)++;
	}
}

void		get_sharp_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '#')
	{
		format_var->sharp_flag = 1;
		(*i)++;
	}
}

void		get_space_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == ' ')
	{
		format_var->space_flag = 1;
		(*i)++;
	}
}

void		get_plus_flag(const char *format, t_format *format_var, int *i)
{
	if (format[*i] == '+')
	{
		format_var->plus_flag = 1;
		(*i)++;
	}
}
