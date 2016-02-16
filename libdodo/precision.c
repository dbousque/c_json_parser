/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:20:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:21:05 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	cut_digits(char **value, t_format *format, int *length)
{
	int		ind;
	char	*tmp;

	ind = 0;
	while (*value && (*value)[ind] && (*value)[ind] != '.')
		ind++;
	if ((*value)[ind] == '.')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (ind + format->precision + 2))))
		{
			tmp = ft_strncpy(tmp, *value, ind + format->precision + 1);
			tmp[ind + format->precision + 1] = '\0';
			free(*value);
			*value = tmp;
			*length = ind + 1 + format->precision;
		}
		else
			*value = NULL;
	}
}

char	is_spec_numb(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'o' || c == 'O' || c == 'u'
		|| c == 'U' || c == 'x' || c == 'X' || c == 'p' || c == 'b' || c == 'f'
		|| c == 'F')
		return (1);
	return (0);
}

void	void_str(char **value, int *length)
{
	free(*value);
	*value = (char*)malloc(sizeof(char));
	(*value)[0] = '\0';
	*length = 0;
}

char	*fill_tmp(t_format *fo, char **value, int res_len, int val_len_without)
{
	int		i;
	int		x;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (fo->precision + res_len + 1))))
		return (NULL);
	tmp[res_len] = '\0';
	i = 0;
	if (fo->neg_val == 1 || fo->has_sign)
	{
		tmp[0] = (*value)[0];
		i = 1;
	}
	x = i;
	i--;
	while (++i < res_len - val_len_without)
		tmp[i] = '0';
	while (i < res_len)
	{
		tmp[i] = (*value)[x];
		i++;
		x++;
	}
	return (tmp);
}

void	apply_precision(char **value, t_format *fo, int *length)
{
	int		val_len;
	int		val_len_without_sign;
	int		res_len;
	char	*tmp;

	val_len = *length;
	val_len_without_sign = (fo->has_sign ? val_len - 1 : val_len);
	if (fo->precision > val_len_without_sign)
	{
		res_len = fo->precision + (val_len - val_len_without_sign);
		*length += res_len - val_len;
		tmp = fill_tmp(fo, value, res_len, val_len_without_sign);
		if (tmp)
		{
			free(*value);
			*value = tmp;
		}
	}
}
