

#ifndef JSON_H
# define JSON_H

# include <fcntl.h>
# include "libdodo.h"

# define BUFF_SIZE 1024
# define LONG 1
# define DOUBLE 2
# define STRING 3
# define DICT 4
# define ARRAY 5

typedef struct	s_value
{
	char		type;
	void		*data;
}				t_value;

typedef struct	s_dict
{
	char		**keys;
	t_value		**values;
}				t_dict;

t_value			*handle_buf(char *buf, int *i);
t_value			*read_json(char *filename);

#endif