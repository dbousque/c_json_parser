

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
# define DELETED_VALUE -1

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

t_value			*read_json(char *filename);
void			print_json(t_value *json);
void			free_value(t_value *value);
t_value			*handle_buf(char *buf, int *i);
double			get_double(t_value *value);
long			get_long(t_value *value);
char			*get_string(t_value *value);
t_value			*get_val(t_value *dict_inp, char *key);
t_value			*get(t_value *array, int i);
t_value			**get_tab(t_value *value);
t_dict			*get_dict(t_value *dict_val);
t_value			*read_json_str(char *content);

#endif
