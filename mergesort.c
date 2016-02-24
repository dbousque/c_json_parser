

#include "mergesort.h"
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

void	merge(void **elts, int start, int end, int (*cmp)(void *elt1, void *elt2))
{
	int		a;
	int		b;
	int		c;
	int		tmp_int;
	void	*tmp;

	printf("BEFORE %d, %d  : ", start, end);
	print_array((int**)elts);
	a = start;
	b = start + ((end - start) / 2);
	c = -1;
	while (1)
	{
		if (a == b)
			a = -1;
		if (c != -1 && a == c)
			a = -1;
		if (b >= end)
			break ;
		if (a == -1 && c == -1)
			break ;
		if (a == -1 && cmp(elts[c], elts[b]) > 0)
		{
			//if a == -1, then c != -1
			tmp = elts[b];
			a = b - 1;
			printf("All Cs decaled\n");
			while (a >= c)
			{
				elts[a + 1] = elts[a];
				a--;
			}
			elts[c] = tmp;
			b++;
			c++;
			a = -1;
		}
		else if (a == -1)
		{
			// in this case, c is not -1 and elts[c] is smaller than elts[b]
			printf("decaling Cs, because a == -1 and elts[b] is bigger\n");
			while (c < b && cmp(elts[c], elts[b]) < 0)
				c++;
			if (c == b)
				c = -1;
		}
		else if (cmp(elts[a], elts[b]) < 0 && (c == -1 || cmp(elts[a], elts[c]) < 0))
		{
			printf("a smaller\n");
			a++;
		}
		else if (cmp(elts[a], elts[b]) < 0)
		{
			// this means that elts[c] is the smallest
			printf("switching As and Cs\n");
			/*while (c < b)
			{
				tmp = elts[a];
				elts[a] = elts[c];
				elts[c] = tmp;
				c++;
				a++;
			}*/
			//tmp = elts[a];
			//elts[a] = elts[c];
			//tmp2 = elts[a + (b - c)];
			//elts[a + (b - c)] = tmp;
			//elts[a + 1] = 
			void *lol[c - a];
			tmp_int = a;
			while (tmp_int < c)
			{
				lol[tmp_int - a] = elts[tmp_int];
				tmp_int++;
			}
			tmp_int = a;
			while (tmp_int < b - (c - a))
			{
				elts[tmp_int] = elts[c + (tmp_int - a)];
				tmp_int++;
			}
			tmp_int = b - (c - a);
			while (tmp_int < b)
			{
				elts[tmp_int] = lol[tmp_int - (b - (c - a))];
				tmp_int++;
			}
		}
		else if (cmp(elts[b], elts[a]) < 0)
		{
			// b is smallest
			printf("b is smallest\n");
			tmp = elts[a];
			elts[a] = elts[b];
			elts[b] = tmp;
			if (c == -1)
				c = b;
			a++;
			b++;
		}
	}
		/*if (a != -1 && cmp(elts[a], elts[b]) < 0 && (c == -1 || cmp(elts[a], elts[c]) < 0))
			a++;
		else if (c != -1 && cmp(elts[c], elts[a]) < 0 && cmp(elts[c], elts[b]) < 0)
		{
			while (a < c && c < b && cmp(elts[c], elts[a]) < 0 && cmp(elts[c], elts[b]) < )
			{
				printf("switching : %d, %d\n", *((int*)elts[a]), *((int*)elts[c]));
				tmp = elts[a];
				elts[a] = elts[c];
				elts[c] = tmp;
				a++;
				c++;
			}
		}
		else
		{
			printf("switching : %d, %d\n", *((int*)elts[a]), *((int*)elts[b]));
			tmp = elts[a];
			elts[a] = elts[b];
			elts[b] = tmp;
			b++;
			a++;
			if (c == -1)
				c = b - 1;
		}
		if (a == b)
			b++;
		if (c == a)
			a = -1;
		if (c == b)
		{
			printf("C RESET\n");
			c = -1;
		}
	}*/
	printf("AFTER  %d, %d  : ", start, end);
	print_array((int**)elts);
}

void	mergesort_(void **elts, int start, int end, int (*cmp)(void *elt1, void *elt2))
{
	if (start >= end - 1)
		return ;
	mergesort_(elts, start, start + ((end - start) / 2), cmp);
	mergesort_(elts, start + ((end - start) / 2), end, cmp);
	merge(elts, start, end, cmp);
}

void	dodo_mergesort(void **elts, int (*cmp)(void *elt1, void *elt2))
{
	int		i;

	i = 0;
	while (elts[i])
		i++;
	mergesort_(elts, 0, i, cmp);
}

int		main(int argc, char **argv)
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
		dodo_mergesort((void**)array, compare_ints);
		print_array(array);
	}
	return (0);
}
