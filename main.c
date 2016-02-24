

#include "gps.h"


#include <stdio.h>

static void	malloc_error(void)
{
	int i = write(2, "Could not allocate enough memory.\n", 34);
	(void)i;
	exit(1);
}

static t_list	*new_list_elt(void *content, int content_size)
{
	t_list	*res;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		malloc_error();
	res->content = content;
	res->content_size = content_size;
	res->next = NULL;
	return (res);
}

t_node	*new_node(long id, double lat, double lon)
{
	t_node	*res;

	if (!(res = (t_node*)malloc(sizeof(t_node))))
		malloc_error();
	res->id = id;
	res->lat = lat;
	res->lon = lon;
	res->ways = NULL;
	res->tmp_ways = NULL;
	res->nb_inter = 0;
	return (res);
}

t_way	*new_way(char type, char oneway, unsigned char maxspeed)
{
	t_way	*res;

	if (!(res = (t_way*)malloc(sizeof(t_way))))
		malloc_error();
	res->type = type;
	res->oneway = oneway;
	res->maxspeed = maxspeed;
	res->nodes = NULL;
	return (res);
}

t_node	**list_to_nodes(t_list *nodes, int nb)
{
	t_node	**res;
	t_list	*tmp;
	int		i;

	if (!(res = (t_node**)malloc(sizeof(t_node*) * (nb + 1))))
		malloc_error();
	res[nb] = NULL;
	i = 0;
	while (nodes)
	{
		res[i] = (t_node*)nodes->content;
		tmp = nodes;
		nodes = nodes->next;
		free(tmp);
		i++;
	}
	return (res);
}

t_node	**get_nodes(t_value *json)
{
	t_list	*nodes;
	t_list	*nodes_end;
	t_node	*tmp_node;
	t_value	**elts;
	t_value	*elt;
	int		i;
	int		nb;

	nodes = NULL;
	nodes_end = NULL;
	elts = get_tab(get_val(json, "elements"));
	i = 0;
	nb = 0;
	while (elts[i])
	{
		elt = elts[i];
		// elt is an osm node
		if (ft_strcmp("node", get_string(get_val(elt, "type"))) == 0)
		{
			tmp_node = new_node(get_long(get_val(elt, "id")), get_double(get_val(elt, "lat")), get_double(get_val(elt, "lon")));
			ft_lstaddend(&nodes_end, new_list_elt(tmp_node, sizeof(t_node)));
			if (!nodes)
				nodes = nodes_end;
			free_value(elt);
			elts[i] = (void*)DELETED_VALUE;
			nb++;
		}
		i++;
	}
	return (list_to_nodes(nodes, nb));
}

char	get_way_type(char *type)
{
	if (ft_strcmp(type, "motorway") == 0)
		return (MOTORWAY);
	if (ft_strcmp(type, "motorway_link") == 0)
		return (MOTORWAY_LINK);
	if (ft_strcmp(type, "trunk") == 0)
		return (TRUNK);
	if (ft_strcmp(type, "trunk_link") == 0)
		return (TRUNK_LINK);
	if (ft_strcmp(type, "primary") == 0)
		return (PRIMARY);
	if (ft_strcmp(type, "primary_link") == 0)
		return (PRIMARY_LINK);
	if (ft_strcmp(type, "secondary") == 0)
		return (SECONDARY);
	if (ft_strcmp(type, "secondary_link") == 0)
		return (SECONDARY_LINK);
	if (ft_strcmp(type, "tertiary") == 0)
		return (TERTIARY);
	if (ft_strcmp(type, "tertiary_link") == 0)
		return (TERTIARY_LINK);
	if (ft_strcmp(type, "unclassified") == 0)
		return (UNCLASSIFIED);
	if (ft_strcmp(type, "unclassified_link") == 0)
		return (UNCLASSIFIED_LINK);
	if (ft_strcmp(type, "residential") == 0)
		return (RESIDENTIAL);
	if (ft_strcmp(type, "residential_link") == 0)
		return (RESIDENTIAL_LINK);
	if (ft_strcmp(type, "service") == 0)
		return (SERVICE);
	if (ft_strcmp(type, "service_link") == 0)
		return (SERVICE_LINK);
	if (ft_strcmp(type, "living_street") == 0)
		return (LIVING_STREET);
	return (0);
}

char	is_way_oneway(char *oneway)
{
	if (!oneway)
		return (0);
	if (ft_strcmp(oneway, "yes") == 0)
		return (1);
	return (0); 
}

char	only_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

unsigned char	get_maxspeed(char *maxspeed)
{
	if (!maxspeed || !only_digits(maxspeed))
		return (90);
	return (ft_atoi(maxspeed));
}

t_way	**list_to_ways(t_list *ways, int nb)
{
	t_way	**res;
	t_list	*tmp;
	int		i;

	if (!(res = (t_way**)malloc(sizeof(t_way*) * (nb + 1))))
		malloc_error();
	res[nb] = NULL;
	i = 0;
	while (ways)
	{
		res[i] = (t_way*)ways->content;
		tmp = ways;
		ways = ways->next;
		free(tmp);
		i++;
	}
	return (res);
}

int		get_nb_nodes2(t_value **nodes)
{
	int		i;

	i = 0;
	while (nodes[i])
		i++;
	return (i);
}

t_list	*get_ways(t_value *json, t_node **nodes, int nb_nodes)
{
	t_list			*ways;
	t_list			*ways_end;
	t_way			*tmp_way;
	t_value			**elts;
	t_value			*elt;
	t_value			*tags;
	t_value			**tmp_nodes;
	int				i;
	int				x;
	int				nb;

	ways = NULL;
	ways_end = NULL;
	elts = get_tab(get_val(json, "elements"));
	i = 0;
	nb = 0;
	while (elts[i])
	{
		elt = elts[i];
		if (elt != (void*)DELETED_VALUE)
		{
			//print_json(elt);
			// elt is an osm way
			if (ft_strcmp("way", get_string(get_val(elt, "type"))) == 0)
			{
				tags = get_val(elt, "tags");
				tmp_way = new_way(get_way_type(get_string(get_val(tags, "highway"))), is_way_oneway(get_string(get_val(tags, "oneway"))), get_maxspeed(get_string(get_val(tags, "maxspeed"))));
				tmp_nodes = get_tab(get_val(elt, "nodes"));
				//print_json(get_val(elt, "nodes"));
				if (!(tmp_way->nodes = (t_node**)malloc(sizeof(t_node*) * (get_nb_nodes2(tmp_nodes) + 1))))
					malloc_error();
				x = 0;
				while (tmp_nodes[x])
				{
					tmp_way->nodes[x] = find_node_by_id(nodes, nb_nodes, get_long(tmp_nodes[x]));
					if (!tmp_way->nodes[x])
					{
						if (x > 0)
							printf("%ld\n", get_long(tmp_nodes[x - 1]));
						else
							printf("0\n");
						printf("%ld\n", get_long(tmp_nodes[x]));
						print_json(get_val(elt, "nodes"));
						printf("LAAAAAAAAAAAAA\n");
					}
					x++;
				}
				tmp_way->nodes[x] = NULL;
				ft_lstaddend(&ways_end, new_list_elt(tmp_way, sizeof(t_way)));
				if (!ways)
					ways = ways_end;
				free_value(elt);
				elts[i] = (void*)DELETED_VALUE;
				nb++;
			}
		}
		i++;
	}
	return (ways);
}

int		compare_nodes(void *node1, void *node2)
{
	if (((t_node*)node1)->id > ((t_node*)node2)->id)
		return (1);
	return (-1);
}

int		get_nodes_length(t_node **nodes)
{
	int		i;

	i = 0;
	while (nodes[i])
		i++;
	return (i);
}

void	print_node(t_node *node)
{
	printf("Node :\n  id  : %ld\n  lat : %f\n  lon : %f\n", node->id, node->lat, node->lon);
}

t_node	*find_node_by_id(t_node **nodes, int nb_nodes, long id)
{
	int		start;
	int		end;

	start = 0;
	end = nb_nodes;
	while (1)
	{
		if (end - start < 2)
		{
			if (nodes[start]->id == id)
				return (nodes[start]);
			return (NULL);
		}
		if (nodes[(start + end) / 2]->id == id)
			return (nodes[(start + end) / 2]);
		if (nodes[(start + end) / 2]->id < id)
			start = (start + end) / 2 + 1;
		else
			end = (start + end) / 2;
	}
	return (NULL);
}

int		get_nb_nodes(t_node **nodes)
{
	int		i;

	i = 0;
	while (nodes[i])
		i++;
	return (i);
}

void	print_way(t_way *way)
{
	int		i;

	printf("Way :\n  oneway : %d\n  type : %d\n  maxspeed : %d\n  nodes : \n", way->oneway, way->type, way->maxspeed);
	i = 0;
	while (way->nodes[i])
	{
		printf("  %ld\n", way->nodes[i]->id);
		i++;
	}
}

void	free_way(t_way *way)
{
	free(way->nodes);
	free(way);
}

t_list	*get_ways_from_inter_nodes(t_list *tmp_ways, t_list *ways_end)
{
	t_way	*tmp_way;
	int		i;
	int		start;
	int		x;
	t_list	*tmp;
	t_list	*ori_end;
	t_way	*n_way;

	ft_lstaddend(&ways_end, new_list_elt(NULL, 0));
	ori_end = ways_end;
	while (tmp_ways != ori_end)
	{
		tmp_way = (t_way*)tmp_ways->content;
		i = 1;
		start = 0;
		while (tmp_way->nodes[i])
		{
			if (tmp_way->nodes[i]->nb_inter > 1 || !tmp_way->nodes[i + 1])
			{
				// multiple ways cross here
				n_way = new_way(tmp_way->type, tmp_way->oneway, tmp_way->maxspeed);
				if (!(n_way->nodes = (t_node**)malloc(sizeof(t_node*) * (i - start + 1))))
					malloc_error();
				n_way->nodes[i - start] = NULL;
				x = start;
				while (start <= i)
				{
					n_way->nodes[start - x] = tmp_way->nodes[start];
					start++;
				}
				n_way->nodes_len = start - x;
				if (!n_way->nodes[0]->tmp_ways)
					n_way->nodes[0]->tmp_ways = new_list();
				list_add(n_way->nodes[0]->tmp_ways, (void*)n_way);
				if (!n_way->nodes[start - x - 1]->tmp_ways)
					n_way->nodes[start - x - 1]->tmp_ways = new_list();
				list_add(n_way->nodes[start - x - 1]->tmp_ways, (void*)n_way);
				ft_lstaddend(&ways_end, new_list_elt(n_way, sizeof(t_way*)));
				start = i;
			}
			i++;
		}
		free_way(tmp_way);
		tmp = tmp_ways;
		tmp_ways = tmp_ways->next;
		free(tmp);
	}
	return (ori_end->next);
}

int		get_nb_ways(t_list *ways)
{
	int		i;

	i = 0;
	while (ways)
	{
		i++;
		ways = ways->next;
	}
	printf("Nb ways in list : %d\n", i);
	return (i);
}

t_way	**resolve_ways(t_list *tmp_ways)
{
	t_list	*end_ways;
	t_list	*ways_list;
	t_way	*tmp_way;
	int		i;

	end_ways = tmp_ways;
	while (end_ways->next)
		end_ways = end_ways->next;
	ways_list = tmp_ways;
	while (ways_list)
	{
		tmp_way = (t_way*)ways_list->content;
		//print_way(tmp_way);
		i = 0;
		while (tmp_way->nodes[i])
		{
			tmp_way->nodes[i]->nb_inter++;
			i++;
		}
		ways_list = ways_list->next;
	}
	tmp_ways = get_ways_from_inter_nodes(tmp_ways, end_ways);
	return (list_to_ways(tmp_ways, get_nb_ways(tmp_ways)));
}

int		main(int argc, char **argv)
{
	t_value	*json;
	t_node	**nodes;
	int		nb_nodes;
	t_list	*tmp_ways;
	t_way	**ways;

	nodes = NULL;
	ways = NULL;
	tmp_ways = NULL;
	if (argc > 1)
	{
		json = read_json(argv[1]);
		nodes = get_nodes(json);
		nb_nodes = get_nb_nodes(nodes);
		quicksort((void**)nodes, compare_nodes);
		tmp_ways = get_ways(json, nodes, nb_nodes);
		free_value(json);
		ways = resolve_ways(tmp_ways);
		(void)ways;
	}
	return (0);
}
