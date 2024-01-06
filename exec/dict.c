/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:49:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:35:02 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*create_dict_node_env(char *env)
{
	char	*key;
	char	*value;
	t_dict	*env_dict;
	char	*assign_loc;

	env_dict = (t_dict *)ft_calloc(1, sizeof(t_dict));
	if (!env_dict)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	env_dict->key = ft_strcdup(env, '=');
	if (!env_dict->key)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	assign_loc = ft_strchr(env_dict->key, '=');
	if (assign_loc)
		*assign_loc = 0;
	value = ft_strchr(env, '=');
	if (value)
	{
		env_dict->value = ft_strdup(value + 1);
		if (!env_dict->value)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
	}
	return (env_dict);
}

void	exchange_node_content(t_dict *dst, t_dict *src)
{
	char	*tmp_value;

	if (!src->value)
	{
		free(src->key);
		free(src->value);
		free(src);
		return ;
	}
	tmp_value = dst->value;
	dst->value = src->value;
	free(src->key);
	free(tmp_value);
	free(src);
	return ;
}

void	add_node_back(t_dict **list, char *env)
{
	t_dict	*tmp;
	t_dict	*prev;
	t_dict	*new_node;
	char	*tmp_value;

	if (!list)
		return ;
	new_node = create_dict_node_env(env);
	if (!new_node)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	if (!(*list))
	{
		*list = new_node;
		return ;
	}
	tmp = (*list);
	prev = tmp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new_node->key) == 0)
			return (exchange_node_content(tmp, new_node));
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new_node;
}

t_dict	*dict_init(char	**envp)
{
	int		idx;
	char	**key_value;
	t_dict	*dict_list;
	t_dict	*tmp;

	if (!envp || !envp[0])
		return (NULL);
	idx = 0;
	dict_list = create_dict_node_env(envp[idx]);
	tmp = dict_list;
	idx++;
	while (envp[idx])
	{
		tmp->next = create_dict_node_env(envp[idx]);
		tmp = tmp->next;
		idx++;
	}
	return (dict_list);
}
