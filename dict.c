/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:49:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 16:59:37 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

t_dict	*create_dict_node_env(char *env)
{
	char	*key;
	char	*value;
	t_dict	*env_dict;
	char	*assign_loc;

	env_dict = (t_dict *)ft_calloc(1, sizeof(t_dict));
	if (!env_dict)
		exit(EXIT_FAILURE);
	env_dict->key = ft_strcdup(env, '=');
	if (!env_dict->key)
		exit(EXIT_FAILURE);
	assign_loc = ft_strchr(env_dict->key, '=');
	if (assign_loc)
		*assign_loc = 0;
	value = ft_strchr(env, '=');
	if (value)
	{
		env_dict->value = ft_strdup(value + 1);
		if (!env_dict->value)
			exit(EXIT_FAILURE);
	}
	return (env_dict);
}

// t_dict	*create_dict_node(char *key, char *value)
// {
// 	char	**key_value;
// 	t_dict	*env_dict;

// 	env_dict = (t_dict *)malloc(sizeof(t_dict));
// 	if (!env_dict)
// 		exit(EXIT_FAILURE);
// 	env_dict->key = ft_strdup(key);
// 	env_dict->value = ft_strdup(value);
// 	env_dict->next = NULL;
// 	if (!env_dict->key || !env_dict->value)
// 		exit(EXIT_FAILURE);
// 	return (env_dict);
// }

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
		exit(EXIT_FAILURE);
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
			return(exchange_node_content(tmp, new_node));
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new_node;
}

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

static char	*generate_env_str(t_dict *env_dict)
{
	char	*tmp_str;
	char	*env;

	if (!env_dict->value)
	{
		env = ft_strdup(env_dict->key);
		if (!env)
			exit(EXIT_FAILURE);
		return (env);
	}
	tmp_str = ft_strjoin(env_dict->key, "=");
	if (!tmp_str)
		exit(EXIT_FAILURE);
	env = ft_strjoin(tmp_str, env_dict->value);
	if (!env)
		exit(EXIT_FAILURE);
	free(tmp_str);
	return (env);
}

char	**generate_envp(t_dict *env_dict)
{
	char	**envp;
	int		size;
	int		idx;
	t_dict	*tmp;

	size = 0;
	tmp = env_dict;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		exit(EXIT_FAILURE);
	idx = -1;
	tmp = env_dict;
	while (++idx < size)
	{
		envp[idx] =	generate_env_str(tmp);
		tmp = tmp->next;
	}
	envp[idx] = NULL;
	return (envp);
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
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
