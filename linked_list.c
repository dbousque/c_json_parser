

#include "linked_list.h"

static void		malloc_error(void)
{
	int i = write(2, "Could not allocate memory.\n", 27);
	(void)i;
	exit(1);
}

t_linked_list	*new_list(void)
{
	t_linked_list	*res;

	if (!(res = (t_linked_list*)malloc(sizeof(t_linked_list))))
		malloc_error();
	res->elts = NULL;
	res->len = 0;
	res->size = 0;
	return (res);
}

void	**list_to_array(t_linked_list *list)
{
	void	**res;
	int		i;

	if (!(res = (void**)malloc(sizeof(void*) * (list->len + 1))))
		malloc_error();
	res[list->len] = NULL;
	i = 0;
	while (i < list->len)
	{
		res[i] = list->elts[i];
		i++;
	}
	return (res);
}

void	free_list(t_linked_list *list)
{
	free(list->elts);
	free(list);
}

void	double_list_size(t_linked_list *list)
{
	void	**new_elts;
	int		i;

	if (!(new_elts = (void**)malloc(sizeof(void*) * (list->size * 2))))
		malloc_error();
	i = 0;
	while (i < list->len)
	{
		new_elts[i] = list->elts[i];
		i++;
	}
	free(list->elts);
	list->elts = new_elts;
	list->size *= 2;
}

void	list_add(t_linked_list *list, void *elt)
{
	if (!list->elts)
	{
		if (!(list->elts = (void**)malloc(sizeof(void*))))
			malloc_error();
		list->size = 1;
	}
	if (list->len >= list->size)
		double_list_size(list);
	list->elts[list->len] = elt;
	list->len++;
}