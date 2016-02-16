/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <dbousque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 11:13:21 by dbousque          #+#    #+#             */
/*   Updated: 2016/01/02 12:14:32 by dbousque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdodo.h"

static void		ft_tmp_function(int *len, t_list *list, t_file **f, int *st)
{
	if (*f)
	{
		*len = 0;
		*st = 0;
		while (list)
		{
			*len += ft_strlen(list->content);
			list = list->next;
		}
		if ((*f)->content)
			*st = ft_strlen((*f)->content);
		if (*st > 0)
			*len += *st;
	}
	else
	{
		while (list && !(*f))
		{
			if (((t_file*)list->content)->fd == *st)
				*f = ((t_file*)list->content);
			list = list->next;
		}
	}
}

static t_file	*ft_find_file(t_list **files, int fd, int *line_ther, int i)
{
	t_file	*file;

	file = NULL;
	ft_tmp_function(&i, *files, &file, &fd);
	if (!file)
	{
		if (!(file = (t_file*)malloc(sizeof(t_file))))
			return (NULL);
		file->fd = fd;
		file->content = NULL;
		if (!(*files))
			ft_lstaddend(files, ft_lstnew(file, sizeof(t_file)));
		else
			ft_lstadd(files, ft_lstnew(file, sizeof(t_file)));
		file = (t_file*)((*files)->content);
	}
	if (file->content)
	{
		while (file->content[i] && file->content[i] != '\n')
			i++;
		if (file->content[i] == '\n')
			*line_ther = i;
	}
	return (file);
}

static int		ft_lst_to_array(t_list *list, t_file *file, int retur, int len)
{
	char	*res;
	int		start;

	if (!list)
		return (retur);
	ft_tmp_function(&len, list, &file, &start);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	res[len] = '\0';
	if (start > 0)
		ft_strncpy(res, file->content, start);
	while (list)
	{
		len = 0;
		while (((char*)list->content)[len])
		{
			res[start + len] = ((char*)list->content)[len];
			len++;
		}
		start += len;
		list = list->next;
	}
	file->content = res;
	return (retur);
}

static int		ft_read_until_newline(t_file *file, int *ind, int x, t_list *li)
{
	char	buf[BUF_SIZE + 1];
	t_list	*list;
	int		i;
	int		ret;

	list = NULL;
	ret = read(file->fd, buf, BUF_SIZE);
	if (ret < 0)
		return (-1);
	while (ret > 0)
	{
		buf[ret] = '\0';
		ft_lstaddend(&li, ft_lstnew(buf, sizeof(char) * (ret + 1)));
		list = (!list ? li : list);
		i = 0;
		while (buf[i] && buf[i] != '\n')
			i++;
		*ind = x + i + (file->content ? ft_strlen(file->content) : 0);
		if (buf[i] == '\n')
			return (ft_lst_to_array(list, file, 1, 0));
		x += ret;
		ret = read(file->fd, buf, BUF_SIZE);
	}
	*ind = x + (file->content ? ft_strlen(file->content) : 0);
	return (ft_lst_to_array(list, file, 0, 0));
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*files = NULL;
	t_file			*file;
	int				res;
	int				ind;
	char			*tmp;

	ind = -1;
	file = ft_find_file(&files, fd, &ind, 0);
	res = 1;
	if (!file || !line || (ind == -1
			&& (res = ft_read_until_newline(file, &ind, 0, NULL)) == -1))
		return (-1);
	*line = (char*)malloc(sizeof(char) * (ind + 1));
	(*line)[ind] = '\0';
	if (file->content)
		ft_strncpy(*line, file->content, ind);
	if (file->content && file->content[ind])
	{
		tmp = ft_strdup(file->content + ind + 1);
		free(file->content);
		file->content = tmp;
	}
	else
		file->content = NULL;
	return (res);
}
