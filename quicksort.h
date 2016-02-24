

#ifndef QUICKSORT_H
# define QUICKSORT_H

# include <unistd.h>
# include <stdlib.h>

void	quicksort(void **array, int (*cmp)(void *elt1, void *elt2));

#endif
