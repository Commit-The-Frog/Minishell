/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:32 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:35:01 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_env_str(t_dict *env_dict)
{
	char	*tmp_str;
	char	*env;

	if (!env_dict->value)
	{
		env = ft_strdup(env_dict->key);
		if (!env)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		return (env);
	}
	tmp_str = ft_strjoin(env_dict->key, "=");
	if (!tmp_str)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	env = ft_strjoin(tmp_str, env_dict->value);
	if (!env)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
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
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	idx = -1;
	tmp = env_dict;
	while (++idx < size)
	{
		envp[idx] = generate_env_str(tmp);
		tmp = tmp->next;
	}
	envp[idx] = NULL;
	return (envp);
}
