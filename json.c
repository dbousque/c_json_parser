

#include "json.h"

void	open_failed(void)
{
	ft_putendl_fd("Could not read file.", 2);
	exit(0);
}

void	malloc_error(void)
{
	write(2, "Could not allocate enough memory.\n", 34);
	exit(1);
}

void	wrong_format(void)
{
	ft_putstr_fd("File format is invalid.\n", 2);
	exit(0);
}

void	no_colon(void)
{
	ft_putendl_fd("No colon found beetween key and value.", 2);
	exit(0);
}

t_dict	*void_json_object(void)
{
	t_dict	*res;

	if (!(res = (t_dict*)malloc(sizeof(t_dict))))
		malloc_error();
	res->keys = NULL;
	res->values = NULL;
	return (res);
}

t_value	*void_value(void)
{
	t_value	*res;

	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = NULL;
	res->type = 0;
	return (res);
}

void	go_to_next_char(char *buf, int *i, char c)
{
	while (buf[*i] && buf[*i] != c)
		(*i)++;
	if (!buf[*i])
		wrong_format();
}

char	*take_up_to_char(char *buf, int *i, char c, char preceed, int *len)
{
	int		start;
	char	*res;

	start = *i;
	while (buf[*i] && (buf[*i] != c || (*i > 0 && buf[*i - 1] == preceed)))
		(*i)++;
	*len = *i - start;
	if (!(res = (char*)malloc(sizeof(char) * (*len + 1))))
		malloc_error();
	res[*len] = '\0';
	return (ft_strncpy(res, buf + start, *len));
}

t_list	*new_list_elt(void *content, int content_size)
{
	t_list	*res;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		malloc_error();
	res->content = content;
	res->content_size = content_size;
	res->next = NULL;
	return (res);
}

t_value	*string_value(char *buf, int *i)
{
	char	*str;
	int		len;
	t_value	*res;

	go_to_next_char(buf, i, '"');
	(*i)++;
	str = take_up_to_char(buf, i, '"', '\\', &len);
	(*i)++;
	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = (void*)str;
	res->type = STRING;
	return (res);
}

t_value	*keys_n_values_to_value(t_list *keys, t_list *values)
{
	int		len;
	t_list	*tmp;
	t_dict	*dict;
	int		i;
	t_value	*ret_val;

	len = 0;
	tmp = keys;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		malloc_error();
	if (!(dict->keys = (char**)malloc(sizeof(char*) * (len + 1))))
		malloc_error();
	if (!(dict->values = (t_value**)malloc(sizeof(t_value*) * (len + 1))))
		malloc_error();
	dict->values[len] = NULL;
	dict->keys[len] = NULL;
	i = 0;
	while (keys)
	{
		dict->keys[i] = (char*)keys->content;
		dict->values[i] = (t_value*)values->content;
		tmp = keys;
		keys = keys->next;
		free(tmp);
		tmp = values;
		values = values->next;
		free(tmp);
		i++;
	}
	if (!(ret_val = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	ret_val->type = DICT;
	ret_val->data = (void*)dict;
	return (ret_val);
}

t_value	*handle_dict(char *buf, int *i)
{
	int		ret;
	t_list	*keys;
	t_list	*keys_end;
	t_list	*values;
	t_list	*values_end;
	char	*tmp_key;
	t_value	*tmp_value;
	int		len;

	keys = NULL;
	keys_end = NULL;
	values = NULL;
	values_end = NULL;
	ret = 1;
	while (ret)
	{
		go_to_next_char(buf, i, '"');
		(*i)++;
		tmp_key = take_up_to_char(buf, i, '"', '\\', &len);
		(*i)++;
		ft_lstaddend(&keys_end, new_list_elt(tmp_key, (len + 1) * sizeof(char)));
		if (!keys)
			keys = keys_end;
		if (buf[*i] != ':')
			no_colon();
		tmp_value = handle_buf(buf, i);
		ft_lstaddend(&values_end, new_list_elt(tmp_value, sizeof(t_value)));
		if (!values)
			values = values_end;
		if (buf[*i] != ',')
			ret = 0;
	}
	go_to_next_char(buf, i, '}');
	(*i)++;
	return (keys_n_values_to_value(keys, values));
}

t_value	*values_list_to_array(t_list *values, int nb)
{
	t_value	*res;
	t_value	**data;
	t_list	*tmp;

	if (!(data = (t_value**)malloc(sizeof(t_value*) * (nb + 1))))
		malloc_error();
	data[nb] = NULL;
	nb = 0;
	while (values)
	{
		data[nb] = (t_value*)values->content;
		tmp = values;
		values = values->next;
		free(tmp);
		nb++;
	}
	if (!(res = (t_value*)malloc(sizeof(t_value))))
		malloc_error();
	res->data = data;
	res->type = ARRAY;
	return (res);
}

t_value	*handle_array(char *buf, int *i)
{
	int		ret;
	t_list	*values;
	t_list	*values_end;
	t_value	*tmp_value;
	int		nb;

	values = NULL;
	values_end = NULL;
	ret = 1;
	nb = 0;
	(*i)++;
	while (ret)
	{
		tmp_value = handle_buf(buf, i);
		ft_lstaddend(&values_end, new_list_elt(tmp_value, sizeof(t_value)));
		if (!values)
			values = values_end;
		if (buf[*i] != ',')
			ret = 0;
		nb++;
	}
	go_to_next_char(buf, i, ']');
	(*i)++;
	return (values_list_to_array(values, nb));
}

t_value	*handle_buf(char *buf, int *i)
{
	while (buf[*i])
	{
		if (buf[*i] == '{')
			return (handle_dict(buf, i));
		if (buf[*i] == '"')
			return (string_value(buf, i));
		if (buf[*i] == '[')
			return (handle_array(buf , i));
		(*i)++;
	}
	return (void_value());
}

char	*read_whole_file(char *filename)
{
	char	*res;
	char	buf[BUFF_SIZE];
	int		size;
	int		ret;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		open_failed();
	size = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		size += ret;
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		open_failed();
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		malloc_error();
	read(fd, res, size);
	res[size] = '\0';
	return (res);
}

void	print_n_tabs(int n)
{
	while (n > 0)
	{
		ft_putchar('\t');
		n--;
	}
}

void	print_elt(t_value *elt, int nb_tabs)
{
	int		i;

	i = 0;
	if (elt->type == DICT)
	{
		ft_putstr("{\n");
		while (((t_dict*)elt->data)->keys[i])
		{
			print_n_tabs(nb_tabs + 1);
			ft_putchar('"');
			ft_putstr(((t_dict*)elt->data)->keys[i]);
			ft_putstr("\": ");
			print_elt(((t_dict*)elt->data)->values[i], nb_tabs + 1);
			if (((t_dict*)elt->data)->keys[i + 1])
				ft_putchar(',');
			ft_putchar('\n');
			i++;
		}
		print_n_tabs(nb_tabs);
		ft_putstr("}\n");
	}
	else if (elt->type == ARRAY)
	{
		ft_putstr("[\n");
		while (((t_value**)elt->data)[i])
		{
			print_elt(((t_value**)elt->data)[i], nb_tabs + 1);
			if (((t_value**)elt->data)[i + 1])
				ft_putchar(',');
			ft_putchar('\n');
			i++;
		}
		print_n_tabs(nb_tabs);
		ft_putstr("]\n");
	}
	else if (elt->type == STRING)
	{
		print_n_tabs(nb_tabs);
		ft_putchar('"');
		ft_putstr((char*)elt->data);
		ft_putchar('"');
	}
}

void	print_json(t_value *json)
{
	print_elt(json, 0);
}

int		main(int argc, char **argv)
{
	char	*filename;
	char	*buf;
	t_value	*json;
	int		i;

	if (argc > 1)
	{
		filename = argv[1];
		i = 0;
		buf = read_whole_file(filename);
		json = handle_buf(buf, &i);
		free(buf);
	}
	print_json(json);
	return (0);
}