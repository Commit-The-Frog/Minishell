/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:06 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/08 20:22:13 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(t_token **list, t_dict *dict)
{
	t_token	*cur;
	
	cur = *list;
	while (cur)
	{
		// if (!(cur->str[0] == '$' && ft_strlen(cur->str) == 1))
		if (ft_strcmp(cur->str, "$") != 0)
			expand_env(cur, dict);
		cur = cur->next;
	}
}

void	remove_empty_token(t_token **list)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *list;
	if (cur->str == NULL)
		*list = NULL;
	while (cur)
	{
		if (cur->next && cur->next->str == NULL)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->str);
			free(tmp);
		}
		cur = cur->next;
	}
}
