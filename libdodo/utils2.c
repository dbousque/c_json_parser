/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/30 16:16:42 by dbousque          #+#    #+#             */
/*   Updated: 2015/12/30 16:17:01 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

int			bad_specifier(char specifier)
{
	if (specifier != 'c' && specifier != 'C' && specifier != 's'
		&& specifier != 'S' && !is_other_maj(specifier))
		return (0);
	return (1);
}

int			invalid_end(char c)
{
	if (c == ' ')
		return (1);
	if (!c || (!ft_isalpha(c) && !ft_isdigit(c))
			|| is_valid_specifier(c) || is_other_maj(c))
		return (0);
	return (1);
}
