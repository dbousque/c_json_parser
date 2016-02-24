

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

/*int		main(void)
{
	t_linked_list	*list;
	int				*tmp;
	int				i;
	char			tmp_char;

	list = new_list();
	i = 0;
	while (i < 10)
	{
		tmp = (int*)malloc(sizeof(int));
		*tmp = i;
		list_add(list, tmp);
		i++;
	}
	i = 0;
	while (i < list->len)
	{
		tmp_char = *((int*)list->elts[i]) + '0';
		write(1, &tmp_char, 1);
		i++;
	}
	return (0);
}*/
