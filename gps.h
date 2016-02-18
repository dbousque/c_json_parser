

#ifndef GPS_H
# define GPS_H

# include "libdodo.h"
# include "json.h"

# define MOTORWAY 1
# define MOTORWAY_LINK 2
# define TRUNK 3
# define TRUNK_LINK 4
# define PRIMARY 5
# define PRIMARY_LINK 6
# define SECONDARY 7
# define SECONDARY_LINK 8
# define TERTIARY 9
# define TERTIARY_LINK 10
# define UNCLASSIFIED 11
# define UNCLASSIFIED_LINK 12
# define RESIDENTIAL 13
# define RESIDENTIAL_LINK 14
# define SERVICE 15
# define SERVICE_LINK 16
# define LIVING_STREET 17

typedef struct		s_node
{
	long			id;
	double			lat;
	double			lon;
}					t_node;

typedef struct		s_way
{
	t_node			**nodes;
	unsigned char	maxspeed;
	char			oneway;
	char			type;
}					t_way;

#endif