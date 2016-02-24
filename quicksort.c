

#include "quicksort.h"

#include <stdio.h>
#include <string.h>

void	print_array(int **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		printf("%d ", *(array[i]));
		i++;
	}
	printf("\n");
}

int		compare_ints(void *elt1, void *elt2)
{
	if (*((int*)elt1) > *((int*)elt2))
		return (1);
	return (-1);
}

void	quicksort_bis(void **array, int start, int end, int (*cmp)(void *elt1, void *elt2))
{
	int		nb_smaller;
	int		i;
	int		a;
	int		z;
	void	*tmp;

	if (end - start <= 1)
		return ;
	nb_smaller = 0;
	i = start;
	while (i < end - 1)
	{
		if (cmp(array[i], array[end - 1]) < 0)
			nb_smaller++;
		i++;
	}
	tmp = array[start + nb_smaller];
	array[start + nb_smaller] = array[end - 1];
	array[end - 1] = tmp;
	a = start;
	z = end - 1;
	while (1)
	{
		while (a < start + nb_smaller && cmp(array[a], array[start + nb_smaller]) < 0)
			a++;
		if (a >= start + nb_smaller)
			break ;
		while (z > start + nb_smaller && cmp(array[z], array[start + nb_smaller]) > 0)
			z--;
		if (z <= start + nb_smaller)
			break;
		tmp = array[a];
		array[a] = array[z];
		array[z] = tmp;
		a++;
		z--;
	}
	quicksort_bis(array, start, start + nb_smaller, cmp);
	quicksort_bis(array, start + nb_smaller + 1, end, cmp);
}

void	quicksort(void **array, int (*cmp)(void *elt1, void *elt2))
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	quicksort_bis(array, 0, i, cmp);
}

/*int		main(int argc, char **argv)
{
	int		**array;
	int		i;

	if (argc > 1)
	{
		i = 1;
		array = (int**)malloc(sizeof(int*) * argc);
		array[argc - 1] = NULL;
		while (i < argc)
		{
			array[i - 1] = (int*)malloc(sizeof(int));
			*(array[i - 1]) = atoi(argv[i]);
			i++;
		}
		quicksort((void**)array, compare_ints);
		print_array(array);
	}
	return (0);
}*/
