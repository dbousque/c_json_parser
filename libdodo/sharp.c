/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 18:26:18 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 18:27:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	sharp_prefix_octal(char **value, int *length, char *tmp)
{
	tmp[*length + 1] = '\0';
	(*length)++;
	tmp[0] = '0';
	ft_strcpy(tmp + 1, *value);
	free(*value);
	*value = tmp;
}

void	sharp_prefix_hexa(char **value, int *length, char *tmp, t_format *forma)
{
	tmp[*length + 2] = '\0';
	(*length) += 2;
	tmp[0] = '0';
	tmp[1] = (forma->specifier == 'x' ? 'x' : 'X');
	ft_strcpy(tmp + 2, *value);
	free(*value);
	*value = tmp;
}

void	add_sharp_prefix(char **value, t_format *format_var, int *length)
{
	char	*tmp;

	if (format_var->specifier == 'o' || format_var->specifier == 'O')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 2))))
			sharp_prefix_octal(value, length, tmp);
		else
			*value = NULL;
	}
	else if (format_var->specifier == 'x' || format_var->specifier == 'X')
	{
		if ((tmp = (char*)malloc(sizeof(char) * (*length + 3))))
			sharp_prefix_hexa(value, length, tmp, format_var);
		else
			*value = NULL;
	}
}

void	add_prefix_for_addr_n_sharp(char **value, t_format *format, int *length)
{
	char	*tmp;
	int		len;

	if (format->specifier == 'p')
	{
		len = ft_strlen(*value);
		if ((tmp = (char*)malloc(sizeof(char) * (len + 1))))
		{
			tmp[len] = '\0';
			tmp[0] = '0';
			tmp[1] = 'x';
			ft_strcpy(tmp + 2, *value);
			free(*value);
			*value = tmp;
			*length += 2;
		}
		else
			*value = NULL;
	}
	else if (format->sharp_flag == 1 && (format->u_value != 0
				|| (format->precision != -1 && format->specifier != 'x')))
		add_sharp_prefix(value, format, length);
}
