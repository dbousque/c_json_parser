/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 17:09:27 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:11:27 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int				pow2(int nb)
{
	int		res;

	res = 1;
	while (nb > 0)
	{
		res *= 2;
		nb--;
	}
	return (res);
}

unsigned char	byte_array_to_uchar(char *byte)
{
	unsigned char	res;
	int				i;

	i = 7;
	res = 0;
	while (i >= 0)
	{
		res += (byte[i] - '0') * pow2(7 - i);
		i--;
	}
	return (res);
}

void			assign_bit(unsigned char *byte, int nb, char val)
{
	byte[nb] = val;
}

void			write_res_to_tmp(char *res, char *tmp, int tmp_length)
{
	int		res_length;
	int		i;

	res_length = ft_strlen(res);
	i = 0;
	while (i < tmp_length - res_length)
	{
		tmp[i] = '0';
		i++;
	}
	while (i < tmp_length)
	{
		tmp[i] = res[i - (tmp_length - res_length)];
		i++;
	}
}

void			cpy_n_bits(char *res, char *tmp, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		res[i] = tmp[i];
		i++;
	}
}
