

#ifndef GPS_H
# define GPS_H

# include "libdodo.h"
# include "json.h"
# include "quicksort.h"
# include "linked_list.h"
# include <math.h>

# define PI 3.14159265359
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

typedef struct s_way t_way;

typedef struct		s_node
{
	long			id;
	double			lat;
	double			lon;
	char			nb_inter;
	t_linked_list	*tmp_ways;
	t_way			**ways;
}					t_node;

typedef struct		s_way
{
	t_node			**nodes;
	short			nodes_len;
	unsigned char	maxspeed;
	char			oneway;
	char			type;
	char			access;
}					t_way;

t_node				*find_node_by_id(t_node **nodes, int nb_nodes, long id);
t_node				**get_nodes(t_value *json);
int					get_nb_nodes(t_node **nodes);
t_list				*get_ways(t_value *json, t_node **nodes, int nb_nodes);
t_way				**resolve_ways(t_list *tmp_ways);
void				validate_nodes(t_node **nodes);
char				*get_type_name(char type);
void				write_ways_to_file(t_way **ways, char *filename);

#endif
