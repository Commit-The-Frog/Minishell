/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:49:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 21:04:10 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

t_dict	*create_dict_node_env(char *env)
{
	char	*key;
	char	*value;
	t_dict	*env_dict;
	char	*assign_loc;

	env_dict = (t_dict *)malloc(sizeof(t_dict));
	if (!env_dict)
		exit(EXIT_FAILURE);
	value = ft_strchr(env, '=');
	if (!value)
		return (NULL);
	value++;
	if (!*value)
		env_dict->value = NULL;
	else
		env_dict->value = ft_strdup(value);
	env_dict->key = ft_strcdup(env, '=');
	assign_loc = ft_strchr(env_dict->key, '=');
	*assign_loc = 0;
	if (!env_dict->key || !env_dict->value)
		exit(EXIT_FAILURE);
	env_dict->env = NULL;
	env_dict->next = NULL;
	return (env_dict);
}

t_dict	*create_dict_node(char *key, char *value)
{
	char	**key_value;
	t_dict	*env_dict;

	env_dict = (t_dict *)malloc(sizeof(t_dict));
	if (!env_dict)
		exit(EXIT_FAILURE);
	env_dict->key = ft_strdup(key);
	env_dict->value = ft_strdup(value);
	env_dict->next = NULL;
	env_dict->env = NULL;
	if (!env_dict->key || !env_dict->value)
		exit(EXIT_FAILURE);
	return (env_dict);
}

void	add_node_back(t_dict **list, char *key, char *value)
{
	t_dict	*tmp;

	if (!list)
		return ;
	if (!(*list))
	{
		*list = create_dict_node(key, value);
		return ;
	}
	tmp = (*list);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_dict_node(key, value);
}

t_dict	*get_node_with_key(t_dict *list, char *key)
{
	t_dict	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
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

static void	generate_env_str(t_dict *env_dict)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(env_dict->key, "=");
	if (!tmp_str)
		exit(EXIT_FAILURE);
	free(env_dict->env);
	if (!env_dict->value)
		env_dict->env = ft_strjoin(tmp_str, "");
	else
		env_dict->env = ft_strjoin(tmp_str, env_dict->value);
	if (!env_dict->env)
		exit(EXIT_FAILURE);
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
		generate_env_str(tmp);
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
		envp[idx] = tmp->env;
		tmp = tmp->next;
	}
	envp[idx] = NULL;
	return (envp);
}
