

#include "gps.h"

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
	return (res);
}

t_list	*get_nodes(t_value *json)
{
	t_list	*nodes;
	t_list	*nodes_end;
	t_node	*tmp_node;
	t_value	**elts;
	t_value	*elt;
	int		i;

	nodes = NULL;
	nodes_end = NULL;
	elts = get_tab(get_val(json, "elements"));
	i = 0;
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
		}
		i++;
	}
	return (nodes);
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

t_list	*get_ways(t_value *json)
{
	t_list			*ways;
	t_list			*ways_end;
	t_way			*tmp_way;
	t_value			**elts;
	t_value			*elt;
	t_value			*tags;
	int				i;

	ways = NULL;
	ways_end = NULL;
	elts = get_tab(get_val(json, "elements"));
	i = 0;
	while (elts[i])
	{
		elt = elts[i];
		if (elt != (void*)DELETED_VALUE)
		{
			// elt is an osm way
			if (ft_strcmp("way", get_string(get_val(elt, "type"))) == 0)
			{
				tags = get_val(elt, "tags");
				tmp_way = new_way(get_way_type(get_string(get_val(tags, "highway"))), is_way_oneway(get_string(get_val(tags, "oneway"))), get_maxspeed(get_string(get_val(tags, "maxspeed"))));
				ft_lstaddend(&ways_end, new_list_elt(tmp_way, sizeof(t_way)));
				if (!ways)
					ways = ways_end;
				free_value(elt);
				elts[i] = (void*)DELETED_VALUE;
			}
		}
		i++;
	}
	return (ways);
}

int		main(int argc, char **argv)
{
	t_value	*json;
	t_list	*nodes;
	t_list	*ways;

	nodes = NULL;
	ways = NULL;
	if (argc > 1)
	{
		json = read_json(argv[1]);
		nodes = get_nodes(json);
		ways = get_ways(json);
		(void)nodes;
		(void)ways;
	}
	return (0);
}