/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_put3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 17:13:42 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:14:37 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		arg_putchar(va_list ap, char flag, char **str, t_format *format_var)
{
	char	res;
	wchar_t	res2;
	int		length;

	length = 1;
	if (flag == L)
	{
		res2 = va_arg(ap, wchar_t);
		length = ft_put_wchar(res2, str);
		format_var->value = res2;
	}
	else
	{
		res = va_arg(ap, int);
		*str = (char*)malloc(sizeof(char) * 2);
		(*str)[0] = (unsigned char)res;
		(*str)[1] = '\0';
		format_var->value = res;
	}
	format_var->characters = 1;
	return (length);
}

int		arg_putwchar(va_list ap, char flag, char **str, t_format *format_var)
{
	wchar_t	res;

	(void)flag;
	res = va_arg(ap, wchar_t);
	format_var->value = res;
	format_var->characters = 1;
	return (ft_put_wchar(res, str));
}

int		arg_putunicode(va_list ap, char flag, char **str, t_format *format_var)
{
	wchar_t	*res;
	int		length;

	(void)flag;
	res = va_arg(ap, wchar_t*);
	if (res)
		length = ft_putunicode(res, str, format_var);
	else
	{
		*str = ft_strdup("(null)");
		return (6);
	}
	format_var->characters = 1;
	return (length);
}

int		arg_putstr(va_list ap, char flag, char **str, t_format *format_var)
{
	char	*res;

	if (flag == L)
		return (arg_putunicode(ap, flag, str, format_var));
	res = va_arg(ap, char*);
	if (res)
		*str = ft_strdup(res);
	else
	{
		*str = ft_strdup("(null)");
		return (6);
	}
	format_var->characters = 1;
	return (ft_strlen(*str));
}

int		arg_putstr_unprint(va_list ap, char flag, char **str, t_format *format)
{
	char	*res;

	(void)flag;
	res = va_arg(ap, char*);
	if (res)
		ft_putstr_unprint(ft_strdup(res), str);
	else
	{
		*str = ft_strdup("(null)");
		return (6);
	}
	format->characters = 1;
	return (ft_strlen(*str));
}
