/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:11:32 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:34:19 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_store	*get_store(t_store **file_list, int fd)
{
	t_store	*ptr;
	t_store	*prev;
	t_store	*new;

	ptr = *file_list;
	prev = *file_list;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		prev = ptr;
		ptr = ptr->next;
	}
	new = (t_store *)malloc(sizeof(t_store));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->eof = 0;
	new->next = NULL;
	new->fd = fd;
	if (!(*file_list))
		*file_list = new;
	else
		prev->next = new;
	return (new);
}
