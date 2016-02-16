/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_unprint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:52:56 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:53:00 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	handle_is_print(char *tmp, char **str, int y)
{
	if (ft_strlen(tmp) == 1)
	{
		(*str)[y + 1] = tmp[0];
		(*str)[y + 2] = ' ';
		(*str)[y] = ' ';
	}
	else if (ft_strlen(tmp) == 2)
	{
		(*str)[y + 2] = tmp[1];
		(*str)[y + 1] = tmp[0];
		(*str)[y] = ' ';
	}
	else
	{
		(*str)[y + 2] = tmp[ft_strlen(tmp) - 1];
		(*str)[y + 1] = tmp[ft_strlen(tmp) - 2];
		(*str)[y] = tmp[ft_strlen(tmp) - 3];
	}
}

int		deal_with_character(char c, char **str, int x, int y)
{
	char	*tmp;

	(*str)[x] = ' ';
	(*str)[x + 2] = ' ';
	if (!ft_isprint(c))
	{
		(*str)[x + 1] = '.';
		if (!(tmp = ft_itoa(c)))
			return (-1);
		handle_is_print(tmp, str, y);
		free(tmp);
		tmp = NULL;
	}
	else
	{
		(*str)[x + 1] = c;
		(*str)[y] = ' ';
		(*str)[y + 1] = ' ';
		(*str)[y + 2] = ' ';
	}
	return (0);
}

void	ft_putstr_unprint(char *inp, char **str)
{
	int		i;
	int		x;
	int		y;

	i = ft_strlen(inp);
	if (!(*str = (char*)malloc(sizeof(char) * (i * 6 + 2))))
		*str = NULL;
	if (*str)
	{
		(*str)[i * 3] = '\n';
		(*str)[i * 6 + 1] = '\0';
		x = 0;
		y = i * 3 + 1;
		i = 0;
		while (str && inp && inp[i])
		{
			if (deal_with_character(inp[i], str, x, y) == -1)
				*str = NULL;
			y += 3;
			x += 3;
			i++;
		}
	}
	free(inp);
	inp = NULL;
}
