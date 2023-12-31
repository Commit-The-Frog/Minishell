/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:50:39 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/14 18:11:58 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lstclear_return(t_list *start, void (*del)(void *))
{
	ft_lstclear(&start, del);
	return (NULL);
}

static t_list	*ft_lst_creater(t_list *lst, t_list *start, \
	void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_tmp;
	void	*new_content;

	tmp = lst;
	new_tmp = start;
	tmp = tmp->next;
	while (tmp)
	{
		new_content = f(tmp->content);
		if (!new_content)
			return (lstclear_return(start, del));
		new_tmp->next = ft_lstnew(new_content);
		tmp = tmp->next;
		new_tmp = new_tmp->next;
		if (!new_tmp)
		{
			del(new_content);
			return (lstclear_return(start, del));
		}
	}
	return (start);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*new_tmp;
	void	*new_content;

	if (!lst)
		return (NULL);
	new_content = f(lst->content);
	if (!new_content)
		return (NULL);
	new_tmp = ft_lstnew(new_content);
	if (!new_tmp)
	{
		del(new_content);
		return (NULL);
	}
	start = new_tmp;
	return (ft_lst_creater(lst, start, f, del));
}
