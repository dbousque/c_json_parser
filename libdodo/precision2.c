/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:28:34 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:28:50 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	cut_string(char **value, int *length, t_format *f)
{
	char	*tmp;

	if ((tmp = (char*)malloc(sizeof(char) * f->precision + 1)))
	{
		tmp[f->precision] = '\0';
		tmp = ft_strncpy(tmp, *value, f->precision);
		free(*value);
		*value = tmp;
		*length = f->precision;
	}
	else
		*value = NULL;
}

void	append_precision_to_value(char **value, t_format *f, int *len, char ori)
{
	if (ori && f->precision > 0 && (f->specifier == 'f' || f->specifier == 'F'))
		cut_digits(value, f, len);
	else if (is_other_maj(f->specifier) || is_spec_numb(f->specifier))
	{
		if (!is_other_maj(f->specifier) && f->precision == 0
			&& ((f->unsigned_val && f->u_value == 0)
				|| (f->unsigned_val == 0 && f->value == 0)))
			void_str(value, len);
		else
			apply_precision(value, f, len);
	}
	else if ((f->specifier == 'r' || f->specifier == 's'
				|| f->specifier == 'S') && f->precision >= 0
			&& f->precision < (int)ft_strlen(*value))
		cut_string(value, len, f);
}
