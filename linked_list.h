

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

#include <unistd.h>
#include <stdlib.h>

typedef struct	s_linked_list
{
	void		**elts;
	int			len;
	int			size;
}				t_linked_list;

t_linked_list	*new_list(void);
void			list_add(t_linked_list *list, void *elt);

#endif
