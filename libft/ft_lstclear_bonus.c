/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bouns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 10:43:38 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/14 12:57:36 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*target;

	tmp = *lst;
	while (tmp)
	{
		target = tmp;
		tmp = tmp->next;
		ft_lstdelone(target, del);
	}
	*lst = NULL;
}
