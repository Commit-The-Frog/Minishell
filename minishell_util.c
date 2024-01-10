/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:51:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 22:37:18 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **lists)
{
	int	idx;

	idx = 0;
	while (lists && lists[idx])
	{
		free(lists[idx]);
		idx++;
	}
	free(lists);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (*c1 - *c2);
}

void	free_token_list(t_token **list)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *list;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->str);
		free(tmp->origin);
		free(tmp);
	}
}
