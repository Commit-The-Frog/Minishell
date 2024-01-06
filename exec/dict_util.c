/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:39:23 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 19:39:38 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

t_dict	*get_node_with_key(t_dict *list, char *key)
{
	t_dict	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	del_node_with_key(t_dict **env_dict, char *key)
{
	t_dict	*tmp;
	t_dict	*prev;

	tmp = *env_dict;
	prev = tmp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp == prev)
				*env_dict = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			tmp = prev->next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
