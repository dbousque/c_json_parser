/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:21:07 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:06:49 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

static void	ft_freedel(t_list *lst)
{
	if (lst != NULL)
	{
		free(lst);
		lst = NULL;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst || !f)
		return (NULL);
	if (!(res = f(lst)))
		return (NULL);
	tmp2 = res;
	tmp = lst->next;
	while (tmp)
	{
		if (!(tmp2->next = f(tmp)))
		{
			ft_freedel(tmp);
			ft_freedel(tmp2);
			return (NULL);
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	ft_freedel(tmp);
	ft_freedel(tmp2);
	return (res);
}
