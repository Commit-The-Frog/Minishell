/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:39:23 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 15:53:28 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_value_with_key(t_dict *list, char *key)
{
	t_dict	*tmp;

	tmp = get_node_with_key(list, key);
	if (!tmp)
		return (NULL);
	return (tmp->value);
}

void	del_one_node(t_dict *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
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
			{
				*env_dict = tmp->next;
				del_one_node(tmp);
				break ;
			}
			else
				prev->next = tmp->next;
			del_one_node(tmp);
			tmp = prev->next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
