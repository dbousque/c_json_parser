

#include "gps.h"

static void	malloc_error(void)
{
	int i = write(2, "Could not allocate enough memory.\n", 34);
	(void)i;
	exit(1);
}

int		compare_nodes(void *node1, void *node2)
{
	if (((t_node*)node1)->id > ((t_node*)node2)->id)
		return (1);
	return (-1);
}

void	read_ways_n_nodes(char *filename, t_node ***nodes, t_way ***ways)
{
	t_value	*json;
	int		nb_nodes;
	t_list	*tmp_ways;

	tmp_ways = NULL;
	json = read_json(filename);
	*nodes = get_nodes(json);
	nb_nodes = get_nb_nodes(*nodes);
	quicksort((void**)*nodes, compare_nodes);
	tmp_ways = get_ways(json, *nodes, nb_nodes);
	free_value(json);
	*ways = resolve_ways(tmp_ways);
	(void)ways;
	validate_nodes(*nodes);
}

char	*read_whole_file2(char *filename)
{
	char	*res;
	char	buf[1024];
	int		size;
	int		ret;
	int		fd;

	fd = open(filename, O_RDONLY);
	size = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
		size += ret;
	close(fd);
	fd = open(filename, O_RDONLY);
	res = (char*)malloc(sizeof(char) * (size + 1));
	read(fd, res, size);
	res[size] = '\0';
	return (res);
}

void	read_ways_n_nodes_directly(char *filename, t_node ***nodes, t_way ***ways)
{
	int		nb_nodes;
	t_list	*tmp_ways;
	char	*file_content;

	tmp_ways = NULL;
	file_content = read_whole_file2(filename);
	*nodes = get_nodes_directly(file_content);
	nb_nodes = get_nb_nodes(*nodes);
	quicksort((void**)*nodes, compare_nodes);
	tmp_ways = get_ways_directly(file_content, *nodes, nb_nodes);
	free(file_content);
	*ways = resolve_ways(tmp_ways);
	(void)ways;
	validate_nodes(*nodes);
}

char  *make_request(char *url)
{
	char	*command;

	command = ft_strjoin(ft_strjoin("curl ", url), " 2>/dev/null > .tmp_adress");
	system(command);
	return (read_whole_file2(".tmp_adress"));
}

void	replace_char(char *str, char to_rep, char rep)
{
	while (*str)
	{
		if (*str == to_rep)
			*str = rep;
		str++;
	}
}

double	deg2rad(double deg)
{
	return (deg * PI / 180.0);
}

double	rad2deg(double rad)
{
	return (rad * 180 / PI);
}

double	get_distance(double lon1, double lat1, double lon2, double lat2)
{
	double	theta;
	double	dist;

	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) +
		cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);
	dist = rad2deg(dist);
	dist *= 60 * 1.1515;
	dist *= 1.609344;
	return (dist);
}

double	get_distance_node(t_node *node1, t_node *node2)
{
	return (get_distance(node1->lon, node1->lat, node2->lon, node2->lat));
}

t_node	*find_closest_node(t_node **nodes, double lon, double lat)
{
	double	closest_distance;
	t_node	*closest;
	int		i;

	closest = NULL;
	i = 0;
	while (nodes[i])
	{
		if (nodes[i]->ways != NULL && (closest == NULL || closest_distance > get_distance(nodes[i]->lon, nodes[i]->lat, lon, lat)))
		{
			closest = nodes[i];
			closest_distance = get_distance(nodes[i]->lon, nodes[i]->lat, lon, lat);
		}
		i++;
	}
	return (closest);
}

t_node	*get_node_from_adress(t_node **nodes, char **adress_name)
{
	char	*url;
	char	*json_content;
	t_value	*json;
	double	lon;
	double	lat;

	ft_putstr("Enter an adress : ");
	get_next_line(1, adress_name);
	replace_char(*adress_name, ' ', '+');
	url = ft_strjoin(ft_strjoin("\"http://nominatim.openstreetmap.org/search?q=", *adress_name), "&polygon=1&addressdetails=1&format=json\"");
	json_content = make_request(url);
	json = read_json_str(json_content);
	lon = ft_atod(get_string(get_val(get_tab(json)[0], "lon")));
	lat = ft_atod(get_string(get_val(get_tab(json)[0], "lat")));
	replace_char(*adress_name, '+', ' ');
	return (find_closest_node(nodes, lon, lat));
}

t_node2	*new_searchnode(t_node2 *from_node, t_node *to_node, t_node *end_node)
{
	t_node2	*res;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		malloc_error();
	res->last_node = to_node;
	res->distance_from_start = from_node->distance_from_start + get_distance_node(from_node->last_node, to_node);
	res->priority = -(res->distance_from_start + get_distance_node(to_node, end_node));
	res->previous_node = from_node->last_node;
	return (res);
}

/* 
	WAAARRNNINNGGG !!!! res->priority should be changed in the following function too
	if we want another priority function (I know, bad design)
*/

t_node2	*new_searchnode_void(t_node *start, t_node *end, t_node *end_node)
{
	t_node2	*res;

	if (!(res = (t_node2*)malloc(sizeof(t_node2))))
		malloc_error();
	res->last_node = end;
	res->distance_from_start = get_distance_node(start, end);
	res->priority = -(res->distance_from_start + get_distance_node(end, end_node));
	res->previous_node = start;
	return (res);
}

t_node	*way_end(t_way *way, t_node *start_node)
{
	if (way->nodes[0] == start_node)
		return (way->nodes[way->nodes_len - 1]);
	return (way->nodes[0]);
}

void	add_start_nodes(t_tree *tree, t_node *start_node, t_node *end_node)
{
	int		i;

	i = 0;
	start_node->distance_from_start = 0.0;
	while (start_node->ways[i])
	{
		ft_add_to_tree2(tree, new_searchnode_void(start_node, way_end(start_node->ways[i], start_node), end_node));
		i++;
	}
}

void	print_best_way(t_node *start_node, t_node *end_node, clock_t start_time, char *start_name, char *end_name)
{
	t_node			*closest_to_start;
	t_way			*best_way;
	t_node 			*current;
	int				i;
	t_linked_list	*ways;
	char			*filename;

	ways = new_list();
	current = end_node;
	while (1)
	{
		i = 0;
		best_way = NULL;
		closest_to_start = NULL;
		//print_node(current);
		//print_node(current->previous_node);
		while (current->ways[i])
		{
			//print_way(current->ways[i]);
			if (way_end(current->ways[i], current) == current->previous_node)
			{
				best_way = current->ways[i];
				closest_to_start = way_end(current->ways[i], current);
				break ;
			}
			i++;
		}
		//ft_printf("node end : %d, %d\n", current->nb_inter, i);
		if (!best_way || !closest_to_start)
			ft_printf("EEERRRORRR\n");
		list_add(ways, (void*)best_way);
		if (closest_to_start == start_node)
			break ;
		current = closest_to_start;
	}
	ft_printf("Found best way in %.3f seconds !\nDistance : %.1fkm\n", (float)(clock() - start_time) / CLOCKS_PER_SEC, end_node->distance_from_start);
	replace_char(start_name, ' ', '_');
	replace_char(end_name, ' ', '_');
	filename = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("shapefiles/", start_name), "__"), end_name), ".ways");
	write_ways_to_file((t_way**)list_to_array(ways), filename);
}

void	free_searchnode(t_node2 *node)
{
	free(node);
}

void	find_best_way(t_node *start_node, t_node *end_node)
{
	t_tree	*tree;
	t_node2	*top_node;
	int		i;
	int		nb_nodes;
	int		tours;

	tours = 1;
	nb_nodes = 0;
	tree = ft_empty_tree();
	add_start_nodes(tree, start_node, end_node);
	while (!is_tree_empty(tree))
	{
		top_node = pop(tree);
		if (tours % 1000 == 0)
			ft_printf("nb nodes : %d\n", tree->last);
		if (tree->last > nb_nodes)
			nb_nodes = tree->last;
		if (top_node->last_node->distance_from_start != -1.0)
			free_searchnode(top_node);
		else
		{
			top_node->last_node->distance_from_start = top_node->distance_from_start;
			top_node->last_node->previous_node = top_node->previous_node;
			if (top_node->last_node == end_node)
			{
				free_searchnode(top_node);
				ft_printf("highest number of nodes : %d\n", nb_nodes);
				return ;
			}
			i = 0;
			while (top_node->last_node->ways[i])
			{
				if (way_end(top_node->last_node->ways[i], top_node->last_node)->distance_from_start == -1.0)
					ft_add_to_tree2(tree, new_searchnode(top_node, way_end(top_node->last_node->ways[i], top_node->last_node), end_node));
				i++;
			}
			free_searchnode(top_node);
		}
		tours++;
	}
	ft_printf("NOT FOUND.\n");
}

void	clean_nodes(t_node **nodes)
{
	int		i;

	i = 0;
	while (nodes[i])
	{
		nodes[i]->distance_from_start = -1.0;
		nodes[i]->previous_node = NULL;
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_node	**nodes;
	t_way	**ways;
	t_node	*start_node;
	t_node	*end_node;
	clock_t	start_time;
	char	*start_name;
	char	*end_name;

	nodes = NULL;
	ways = NULL;
	if (argc > 1)
	{
		read_ways_n_nodes_directly(argv[1], &nodes, &ways);
		//write_ways_to_file(ways, "shapefiles/all_ways5.ways");
		while (1)
		{
			start_node = get_node_from_adress(nodes, &start_name);
			end_node = get_node_from_adress(nodes, &end_name);
			//(void)start_node;
			//(void)end_node;
			//start_node = find_closest_node(nodes, 2.353337, 48.890366);
			//end_node = find_closest_node(nodes, 2.256107, 48.841455);
			start_time = clock();
			find_best_way(start_node, end_node);
			print_best_way(start_node, end_node, start_time, start_name, end_name);
			clean_nodes(nodes);
		}
	}
	return (0);
}
