/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 14:56:36 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:11:20 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void		ft_putstr2(char *str, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		ft_putchar(str[i]);
		i++;
	}
}

void		prepend_plus_space_flags(char **val, t_format *format, int *len)
{
	char	*tmp;

	if ((format->plus_flag || format->space_flag) && !format->neg_val)
	{
		format->has_sign = 1;
		if ((tmp = (char*)malloc(sizeof(char) * (*len + 2))))
		{
			tmp[*len + 1] = '\0';
			tmp[0] = (format->plus_flag ? '+' : ' ');
			ft_memcpy(tmp + 1, *val, *len);
			free(*val);
			*val = tmp;
			(*len)++;
		}
		else
			*val = NULL;
	}
}

int			get_decal(t_format *format)
{
	int		decal;

	decal = (format->specifier == 'p' && format->char_to_fill == '0' ? 2 : 0);
	if (format->char_to_fill == '0' && decal == 0 && format->sharp_flag == 1)
	{
		if (format->specifier == 'o' || format->specifier == 'O')
			decal = 1;
		else if (format->specifier == 'x' || format->specifier == 'X')
			decal = 2;
	}
	return (decal);
}

void		width_n_prefix(char **value, t_format *format, int *len, int o_done)
{
	int		decal;

	decal = get_decal(format);
	if (is_valid_specifier(format->specifier))
		append_precision_to_value(value, format, len, 1);
	if (!format->minus_flag)
	{
		if (!o_done && format->char_to_fill == ' ')
			add_prefix_for_addr_n_sharp(value, format, len);
		ajust_value_to_width(value, format, len, decal);
		if (!o_done && format->char_to_fill == '0')
			add_prefix_for_addr_n_sharp(value, format, len);
	}
	else
	{
		if (!o_done)
			add_prefix_for_addr_n_sharp(value, format, len);
		ajust_value_to_width_minus(value, format, len);
	}
}

int			print_format(t_format *format, va_list ap)
{
	char	*value;
	int		length;
	int		o_done;

	o_done = 0;
	length = get_arg(&value, ap, format);
	if (format->neg_val == 1)
		format->has_sign = 1;
	if (format->specifier == 'd' || format->specifier == 'D'
			|| format->specifier == 'i' || format->specifier == 'b'
			|| format->specifier == 'f' || format->specifier == 'F')
		prepend_plus_space_flags(&value, format, &length);
	if (format->sharp_flag && (format->specifier == 'o'
				|| format->specifier == 'O') && format->precision != 0)
	{
		o_done = 1;
		add_prefix_for_addr_n_sharp(&value, format, &length);
	}
	width_n_prefix(&value, format, &length, o_done);
	ft_putstr2(value, length);
	if (value)
		free(value);
	return (length);
}
