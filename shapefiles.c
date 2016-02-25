

#include "gps.h"

char	*boolean_to_str(char bool)
{
	if (bool == 1)
		return ("true");
	else if (bool == 0)
		return ("false");
	return ("ERROR");
}

void	write_ways_to_file(t_way **ways, char *filename)
{
	int		fd;
	int		i;
	int		x;
	char	*coord;

	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT);
	i = 0;
	coord = NULL;
	while (ways[i])
	{
		write(fd, get_type_name(ways[i]->type), ft_strlen(get_type_name(ways[i]->type)));
		write(fd, "\n", 1);
		write(fd, ft_itoa(ways[i]->maxspeed), ft_strlen(ft_itoa(ways[i]->maxspeed)));
		write(fd, "\n", 1);
		write(fd, boolean_to_str(ways[i]->oneway), ft_strlen(boolean_to_str(ways[i]->oneway)));
		write(fd, "\n", 1);
		write(fd, boolean_to_str(ways[i]->access), ft_strlen(boolean_to_str(ways[i]->access)));
		write(fd, "\n", 1);
		x = 0;
		while (ways[i]->nodes[x])
		{
			ft_putdouble(ways[i]->nodes[x]->lon, &coord);
			write(fd, coord, ft_strlen(coord));
			write(fd, ",", 1);
			ft_putdouble(ways[i]->nodes[x]->lat, &coord);
			write(fd, coord, ft_strlen(coord));
			write(fd, "\n", 1);
			x++;
		}
		if (ways[i + 1])
			write(fd, "\n", 1);
		i++;
	}
	close(fd);
}