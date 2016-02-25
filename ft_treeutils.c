/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 16:22:24 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 19:38:24 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gps.h"

int			ft_first_higher(t_tree *tree, int ind1, int ind2)
{
	if (tree->tree[ind1]->priority > tree->tree[ind2]->priority)
		return (1);
	return (0);
}

t_node2		*ft_swap(t_tree *tree, int *ind, int ind2, t_node2 *tmp)
{
	tmp = tree->tree[ind2];
	tree->tree[ind2] = tree->tree[*ind];
	tree->tree[*ind] = tmp;
	*ind = ind2;
	return (tmp);
}

t_node2		*ft_get_res_n_update(t_tree *tree)
{
	t_node2		*res;

	res = tree->tree[1];
	tree->tree[1] = tree->tree[tree->last];
	tree->tree[tree->last] = NULL;
	tree->last -= 1;
	return (res);
}

int			ft_right_place(int *ind, t_tree *tree)
{
	if (*ind * 2 > tree->last || (!tree->tree[*ind * 2]
			&& !tree->tree[*ind * 2 + 1])
		|| (ft_first_higher(tree, *ind, *ind * 2) && (!tree->tree[*ind * 2 + 1]
				|| ft_first_higher(tree, *ind, *ind * 2 + 1))))
		return (1);
	return (0);
}
