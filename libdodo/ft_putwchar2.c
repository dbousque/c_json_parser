/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:58:07 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:59:14 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_put_three_uni_part2(char *val[3], char tmp[17], char *str)
{
	if (!(val[2] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 10, 6);
	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	str[2] = byte_array_to_uchar(val[2]);
	free(val[0]);
	free(val[1]);
	free(val[2]);
	val[0] = NULL;
	val[1] = NULL;
	val[2] = NULL;
	return (3);
}

int		ft_put_three_uni(wchar_t car, char *str)
{
	char	*val[3];
	char	tmp[17];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 16);
	if (res)
		free(res);
	tmp[16] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '0';
	cpy_n_bits(val[0] + 4, tmp, 4);
	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 4, 6);
	return (ft_put_three_uni_part2(val, tmp, str));
}

int		ft_put_four_uni_part2(char *val[4], char tmp[22], char *str)
{
	val[2][0] = '1';
	val[2][1] = '0';
	cpy_n_bits(val[2] + 2, tmp + 9, 6);
	if (!(val[3] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[3][0] = '1';
	val[3][1] = '0';
	cpy_n_bits(val[3] + 2, tmp + 15, 6);
	str[0] = byte_array_to_uchar(val[0]);
	str[1] = byte_array_to_uchar(val[1]);
	str[2] = byte_array_to_uchar(val[2]);
	str[3] = byte_array_to_uchar(val[3]);
	free(val[0]);
	free(val[1]);
	free(val[2]);
	free(val[3]);
	val[0] = NULL;
	val[1] = NULL;
	val[2] = NULL;
	val[3] = NULL;
	return (4);
}

int		ft_put_four_uni(wchar_t car, char *str)
{
	char	*val[4];
	char	tmp[22];
	char	*res;

	res = ft_ntoa_base_un((unsigned int)car, "01");
	write_res_to_tmp(res, tmp, 21);
	if (res)
		free(res);
	tmp[21] = '\0';
	if (!(val[0] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[0][0] = '1';
	val[0][1] = '1';
	val[0][2] = '1';
	val[0][3] = '1';
	val[0][4] = '0';
	cpy_n_bits(val[0] + 5, tmp, 3);
	if (!(val[1] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	val[1][0] = '1';
	val[1][1] = '0';
	cpy_n_bits(val[1] + 2, tmp + 3, 6);
	if (!(val[2] = (char*)malloc(sizeof(char) * 8)))
		return (0);
	return (ft_put_four_uni_part2(val, tmp, str));
}
