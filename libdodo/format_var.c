/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:29:57 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:30:08 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void		free_format(t_format *format)
{
	if (format)
		free(format);
	format = NULL;
}

t_format	*new_format(void)
{
	t_format	*format_var;

	if (!(format_var = (t_format*)malloc(sizeof(t_format))))
		return (NULL);
	format_var->char_to_fill = ' ';
	format_var->neg_val = 0;
	format_var->unsigned_val = 0;
	format_var->has_sign = 0;
	format_var->characters = 0;
	format_var->length = -1;
	format_var->width = -1;
	format_var->precision = -1;
	format_var->specifier = -1;
	format_var->plus_flag = 0;
	format_var->sharp_flag = 0;
	format_var->space_flag = 0;
	format_var->minus_flag = 0;
	format_var->value = 0;
	format_var->u_value = 0;
	return (format_var);
}
