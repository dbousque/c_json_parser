

#include "gps.h"

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

t_node	*get_node_from_adress(t_node **nodes)
{
	char	*adress;
	char	*url;
	char	*json_content;
	t_value	*json;
	double	lon;
	double	lat;

	ft_putstr("Enter an adress : ");
	get_next_line(1, &adress);
	replace_char(adress, ' ', '+');
	url = ft_strjoin(ft_strjoin("\"http://nominatim.openstreetmap.org/search?q=", adress), "&polygon=1&addressdetails=1&format=json\"");
	json_content = make_request(url);
	json = read_json_str(json_content);
	lon = ft_atod(get_string(get_val(get_tab(json)[0], "lon")));
	lat = ft_atod(get_string(get_val(get_tab(json)[0], "lat")));
	return (find_closest_node(nodes, lon, lat));
}

int		main(int argc, char **argv)
{
	t_node	**nodes;
	t_way	**ways;
	t_node	*start_node;
	t_node	*end_node;

	nodes = NULL;
	ways = NULL;
	if (argc > 1)
	{
		read_ways_n_nodes(argv[1], &nodes, &ways);
		write_ways_to_file(ways, "shapefiles/all_ways.ways");
		start_node = get_node_from_adress(nodes);
		end_node = get_node_from_adress(nodes);
		(void)start_node;
		(void)end_node;
		ft_printf("node lat lon : %f, %f\n", start_node->lon, start_node->lat);
	}
	return (0);
}
