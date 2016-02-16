/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:22:27 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:22:43 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int		ft_find_color(char *color, const char *format, int *i, char *finished)
{
	int		len;
	int		remaining_chars;
	char	*tmp;

	len = ft_strlen(color);
	remaining_chars = ft_strlen(format + *i);
	if (len < remaining_chars
		&& (format[*i + len + 1] == '}' || format[*i + len + 1] == ';'))
	{
		tmp = ft_strsub(format, *i + 1, len);
		if (ft_strcmp(tmp, color) == 0)
		{
			if (format[*i + len + 1] == '}')
				*finished = 1;
			free(tmp);
			tmp = NULL;
			*i += len + 1;
			return (len);
		}
		free(tmp);
		tmp = NULL;
	}
	return (0);
}

char	ft_find_fg_color(const char *format, int *i, char *finished, int *len)
{
	if ((*len = ft_find_color("eoc", format, i, finished)))
		return (FG_WHITE);
	if ((*len = ft_find_color("red", format, i, finished)))
		return (FG_RED);
	if ((*len = ft_find_color("black", format, i, finished)))
		return (FG_BLACK);
	if ((*len = ft_find_color("green", format, i, finished)))
		return (FG_GREEN);
	if ((*len = ft_find_color("yellow", format, i, finished)))
		return (FG_YELLOW);
	if ((*len = ft_find_color("blue", format, i, finished)))
		return (FG_BLUE);
	if ((*len = ft_find_color("magenta", format, i, finished)))
		return (FG_MAGENTA);
	if ((*len = ft_find_color("cyan", format, i, finished)))
		return (FG_CYAN);
	return (FG_WHITE);
}

char	ft_find_bg_color(const char *format, int *i, char *finished)
{
	if (ft_find_color("red", format, i, finished))
		return (BG_RED);
	if (ft_find_color("green", format, i, finished))
		return (BG_GREEN);
	if (ft_find_color("yellow", format, i, finished))
		return (BG_YELLOW);
	if (ft_find_color("blue", format, i, finished))
		return (BG_BLUE);
	if (ft_find_color("magenta", format, i, finished))
		return (BG_MAGENTA);
	if (ft_find_color("cyan", format, i, finished))
		return (BG_CYAN);
	if (ft_find_color("white", format, i, finished))
		return (BG_WHITE);
	return (BG_BLACK);
}

void	ft_putcolor(char attr, char fg, char bg)
{
	ft_putstr("[");
	ft_putnbr(attr);
	ft_putchar(';');
	ft_putnbr(fg);
	ft_putchar(';');
	ft_putnbr(bg);
	ft_putchar('m');
}

void	ft_change_color_if_asked(const char *format, int *i)
{
	char	fg;
	char	bg;
	char	finished;
	int		len;

	len = 0;
	finished = 0;
	bg = BG_BLACK;
	fg = ft_find_fg_color(format, i, &finished, &len);
	if (len > 0 && !finished)
	{
		bg = ft_find_bg_color(format, i, &finished);
		if (!finished)
			*i -= (len + 1);
	}
	if (finished && fg)
	{
		(*i)++;
		ft_putcolor(ATTR_RESET, fg, bg);
	}
}
