

#ifndef JSON_H
# define JSON_H

# include <fcntl.h>
# include "libdodo.h"

# define BUFF_SIZE 1024
# define INT 1
# define LONG 2
# define DOUBLE 3
# define STRING 4
# define DICT 5
# define ARRAY 6

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

#endif