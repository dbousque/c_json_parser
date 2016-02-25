/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 12:09:47 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 19:48:06 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gps.h"

t_tree		*ft_double_tree_size(t_tree *tree)
{
	t_node2		**res;
	int			i;

	if (!(res = (t_node2**)malloc(sizeof(t_node2*) * (tree->max_size * 2 + 1))))
		return (NULL);
	i = 1;
	while (i <= tree->max_size)
	{
		res[i] = tree->tree[i];
		if (i > tree->max_size)
			res[i] = NULL;
		i++;
	}
	tree->max_size *= 2;
	free(tree->tree);
	tree->tree = res;
	return (tree);
}

t_tree		*ft_add_to_tree2(t_tree *tree, t_node2 *node)
{
	int			i;
	int			ind;
	t_node2		*tmp;

	if (tree->last + 1 > tree->max_size)
		tree = ft_double_tree_size(tree);
	tree->last += 1;
	tree->tree[tree->last] = node;
	i = tree->last;
	while (i > 1)
	{
		ind = (i - (i % 2)) / 2;
		if (tree->tree[ind]->priority >= tree->tree[i]->priority)
			return (tree);
		tmp = tree->tree[ind];
		tree->tree[ind] = tree->tree[i];
		tree->tree[i] = tmp;
		i = ind;
	}
	return (tree);
}

t_node2		*pop(t_tree *tree)
{
	t_node2		*res;
	t_node2		*tmp;
	int			ind;
	int			go_on;

	go_on = 1;
	res = ft_get_res_n_update(tree);
	ind = 1;
	tmp = NULL;
	while (go_on)
	{
		if (ft_right_place(&ind, tree))
			go_on = 0;
		else
		{
			if (tree->tree[ind * 2] && (!tree->tree[ind * 2 + 1]
					|| ft_first_higher(tree, ind * 2, ind * 2 + 1)))
				tmp = ft_swap(tree, &ind, ind * 2, tmp);
			else
				tmp = ft_swap(tree, &ind, ind * 2 + 1, tmp);
		}
	}
	tmp = NULL;
	return (res);
}

char		is_tree_empty(t_tree *tree)
{
	if (tree->last <= 0)
		return (1);
	return (0);
}

t_tree		*ft_empty_tree(void)
{
	t_tree		*tree;

	if (!(tree = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	if (!(tree->tree = (t_node2**)malloc(sizeof(t_node2*) * 2)))
		return (NULL);
	tree->tree[1] = NULL;
	tree->last = 0;
	tree->nb_elts = 0;
	tree->max_size = 1;
	return (tree);
}
