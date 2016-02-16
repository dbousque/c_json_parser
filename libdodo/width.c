/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:23:45 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:24:17 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	ajust_value_to_width_minus(char **value, t_format *format_var, int *len)
{
	char	*tmp;

	if (format_var->width > *len)
	{
		if ((tmp = (char*)malloc(sizeof(char) * (format_var->width + 1))))
		{
			tmp[format_var->width] = '\0';
			ft_memcpy(tmp, *value, *len);
			while (*len < format_var->width)
			{
				tmp[*len] = ' ';
				(*len)++;
			}
			free(*value);
			*value = tmp;
		}
		else
			*value = NULL;
	}
}

void	ajust_value_with_zeros(char **value, t_format *forma, int *len, int dec)
{
	int		ori_precision;
	char	ori_specifier;

	ori_precision = forma->precision;
	ori_specifier = forma->specifier;
	if (forma->has_sign == 1)
		forma->precision = forma->width - 1;
	else
		forma->precision = forma->width;
	forma->precision -= dec;
	forma->specifier = 'd';
	append_precision_to_value(value, forma, len, 0);
	forma->precision = ori_precision;
	forma->specifier = ori_specifier;
}

void	ajust_value_with_spaces(char **value, t_format *forma, int *len, int va)
{
	char	*tmp;
	int		i;

	if ((tmp = (char*)malloc(sizeof(char) * (forma->width + 1))))
	{
		tmp[forma->width] = '\0';
		i = va;
		while (va < forma->width)
		{
			tmp[va - i] = ' ';
			va++;
			(*len)++;
		}
		ft_memcpy(tmp + (va - i), *value, forma->width - (va - i));
		free(*value);
		*value = tmp;
	}
	else
		*value = NULL;
}

void	ajust_value_to_width(char **value, t_format *forma, int *len, int decal)
{
	int		val_len;

	val_len = *len + decal;
	if (forma->width > val_len)
	{
		if (forma->char_to_fill == '0')
			ajust_value_with_zeros(value, forma, len, decal);
		else
			ajust_value_with_spaces(value, forma, len, val_len);
	}
}
