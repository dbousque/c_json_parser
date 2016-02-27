

#ifndef GPS_H
# define GPS_H

# include "libdodo.h"
# include "json.h"
# include "quicksort.h"
# include "linked_list.h"
# include <math.h>
# include <time.h>

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
	double			distance_from_start;
	struct s_node	*previous_node;
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

typedef struct		s_node2
{
	t_node			*last_node;
	double			distance_from_start;
	t_node			*previous_node;
	double			priority;
}					t_node2;

typedef struct		s_tree
{
	t_node2			**tree;
	int				max_size;
	int				nb_elts;
	int				last;
}					t_tree;

t_node				*find_node_by_id(t_node **nodes, int nb_nodes, long id);
t_node				**get_nodes(t_value *json);
int					get_nb_nodes(t_node **nodes);
t_list				*get_ways(t_value *json, t_node **nodes, int nb_nodes);
t_list				*get_ways_directly(char *file_content, t_node **nodes, int nb_nodes);
t_way				**resolve_ways(t_list *tmp_ways);
void				validate_nodes(t_node **nodes);
char				*get_type_name(char type);
void				write_ways_to_file(t_way **ways, char *filename);
t_tree				*ft_empty_tree(void);
t_tree				*ft_add_to_tree2(t_tree *tree, t_node2 *node);
t_node2				*pop(t_tree *tree);
t_node2				*ft_get_res_n_update(t_tree *tree);
t_node2				*ft_swap(t_tree *tree, int *ind, int ind2, t_node2 *tmp);
char				is_tree_empty(t_tree *tree);
int					ft_right_place(int *ind, t_tree *tree);
int					ft_first_higher(t_tree *tree, int ind1, int ind2);
void				print_way(t_way *way);
void				print_node(t_node *node);
t_value				*get_elt_from_file(char **file_content);
char				has_next_elt(char *file_content);
char				*next_json_start(char *file_content);
void				get_to_elts_start(char **file_content);
t_node				**get_nodes_directly(char *file_content);

#endif
