/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/19 15:59:06 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 17:10:10 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	del_maillon(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
	content = NULL;
}

char	*lst_to_str(t_list *strs)
{
	t_list	*tmp;
	int		length;
	char	*res;

	tmp = strs;
	length = 0;
	while (tmp)
	{
		length += tmp->content_size - 1;
		tmp = tmp->next;
	}
	if (!(res = (char*)malloc(sizeof(char) * (length + 1))))
		return (NULL);
	res[length] = '\0';
	length = 0;
	tmp = strs;
	while (strs)
	{
		ft_strcpy(res + length, strs->content);
		length += strs->content_size - 1;
		strs = strs->next;
	}
	ft_lstdel(&tmp, del_maillon);
	return (res);
}

int		empty_str(char **str)
{
	if ((*str = (char*)malloc(sizeof(char))))
		(*str)[0] = '\0';
	else
		*str = NULL;
	return (0);
}

char	handle_tmp_wchar(wchar_t car, t_format *format, int *len, t_list **strs)
{
	char	*tmp;
	int		tmp_len;

	tmp = NULL;
	tmp_len = ft_put_wchar(car, &tmp);
	if (!tmp)
		return (-1);
	if (format->precision == -1 || *len + tmp_len <= format->precision)
	{
		ft_lstaddend(strs, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		*len += tmp_len;
	}
	free(tmp);
	return (tmp_len);
}

int		ft_putunicode(wchar_t *uni, char **str, t_format *fo)
{
	int		i;
	int		length;
	int		tmp_len;
	t_list	*strs;
	t_list	*strs_end;

	strs = NULL;
	strs_end = NULL;
	i = 0;
	length = 0;
	tmp_len = 0;
	while (uni[i] && (fo->precision == -1 || length + tmp_len <= fo->precision))
	{
		if ((tmp_len = handle_tmp_wchar(uni[i], fo, &length, &strs_end)) == -1)
			return (empty_str(str));
		if (!strs)
			strs = strs_end;
		i++;
	}
	*str = lst_to_str(strs);
	return (length);
}
