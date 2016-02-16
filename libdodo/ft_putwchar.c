/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:55:31 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:57:47 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_put_one_uni(wchar_t car, char *str)
{
	str[0] = (unsigned char)car;
	str[1] = '\0';
	return (1);
}

int		ft_put_two_uni_part2(char *val[2], char tmp[12], char *str)
{
	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 5, 6);
	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	free(val[0]);
	free(val[1]);
	val[0] = NULL;
	val[1] = NULL;
	return (2);
}

int		ft_put_two_uni(wchar_t car, char *str)
{
	char	*val[2];
	char	tmp[12];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 11);
	if (res)
		free(res);
	res = NULL;
	tmp[11] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '0';
	cpy_n_bits(val[0] + 3, tmp, 5);
	return (ft_put_two_uni_part2(val, tmp, str));
}

int		ft_put_wchar_part2(wchar_t car, char **str)
{
	if (car < 0x0000FFFF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 4)))
			return (0);
		(*str)[3] = '\0';
		return (ft_put_three_uni(car, *str));
	}
	if (car < 0x001FFFFF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 5)))
			return (0);
		(*str)[4] = '\0';
		return (ft_put_four_uni(car, *str));
	}
	return (0);
}

int		ft_put_wchar(wchar_t car, char **str)
{
	if (car < 0x0000007F)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 2)))
			return (0);
		(*str)[1] = '\0';
		return (ft_put_one_uni(car, *str));
	}
	if (car < 0x000007FF)
	{
		if (!(*str = (char*)malloc(sizeof(char) * 3)))
			return (0);
		(*str)[2] = '\0';
		return (ft_put_two_uni(car, *str));
	}
	return (ft_put_wchar_part2(car, str));
}
