/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:11:48 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/20 14:19:04 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_new_read(t_store *store, char *buf)
{
	char	*temp;

	temp = ft_strjoin(store->content, buf);
	free(buf);
	free(store->content);
	store->content = temp;
	if (!temp)
		return (-1);
	return (1);
}

static int	put_new_read(int fd, t_store *store, int extend)
{
	char	*buf;
	int		i;
	ssize_t	read_size;
	ssize_t	cur_read_size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE * extend + 1));
	if (!buf)
		return (-1);
	i = 0;
	read_size = 0;
	while (i < extend && !store->eof)
	{
		cur_read_size = read(fd, &buf[i * BUFFER_SIZE], BUFFER_SIZE);
		if (cur_read_size < 0)
		{
			free(buf);
			return (-1);
		}
		read_size += cur_read_size;
		if (cur_read_size == 0)
			store->eof = 1;
		i++;
	}
	buf[read_size] = 0;
	return (return_new_read(store, buf));
}

static char	*free_store(t_store **file_list, int fd)
{
	t_store	*temp;
	t_store	*prev;

	prev = *file_list;
	temp = *file_list;
	while (temp)
	{
		if (temp->fd == fd)
			break ;
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	if (temp == *file_list)
		*file_list = temp->next;
	prev->next = temp->next;
	free(temp->content);
	free(temp);
	temp = NULL;
	return (NULL);
}

static char	*return_line(t_store **store, char *n_loc, t_store **f_list, int fd)
{
	char	*temp;
	char	*line;

	if (!n_loc)
	{
		if (!(*store)->content || ft_strlen((*store)->content) == 0)
			line = NULL;
		else
			line = ft_strcdup((*store)->content, 0);
		free_store(f_list, fd);
		return (line);
	}
	line = ft_strcdup((*store)->content, '\n');
	if (!line)
		return (free_store(f_list, fd));
	temp = (*store)->content;
	(*store)->content = ft_strcdup(n_loc + 1, 0);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_store	*file_list = NULL;
	t_store			*store;
	char			*n_loc;
	int				read_result;
	int				buf_extend;

	if (!BUFFER_SIZE)
		return (NULL);
	store = get_store(&file_list, fd);
	buf_extend = 0;
	if (!store)
		return (NULL);
	n_loc = ft_strchr(store->content, '\n');
	while (!n_loc && !store->eof)
	{
		buf_extend++;
		read_result = put_new_read(fd, store, buf_extend);
		if (read_result < 0)
			return (free_store(&file_list, fd));
		n_loc = ft_strchr(store->content, '\n');
	}
	return (return_line(&store, n_loc, &file_list, fd));
}
