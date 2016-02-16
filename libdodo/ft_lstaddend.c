/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 17:57:14 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:04:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

void	ft_lstaddend(t_list **alst, t_list *new)
{
	if (new && *alst)
	{
		(*alst)->next = new;
		*alst = new;
	}
	else
		*alst = new;
}
