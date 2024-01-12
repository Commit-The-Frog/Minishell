/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:32 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 17:40:34 by minjacho         ###   ########.fr       */
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

static int	get_env_size(t_dict *env_dict)
{
	t_dict	*tmp;
	int		size;

	size = 0;
	tmp = env_dict;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

char	**generate_envp(t_dict *env_dict)
{
	char	**envp;
	int		size;
	int		idx;
	t_dict	*tmp;

	size = get_env_size(env_dict);
	envp = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!envp)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	idx = 0;
	tmp = env_dict;
	while (idx < size)
	{
		envp[idx] = generate_env_str(tmp);
		tmp = tmp->next;
		idx++;
	}
	return (envp);
}

int	invalid_id_err(char *func_name, char *str)
{
	const char	*err_str = ": not a valid identifier\n";

	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, func_name, ft_strlen(func_name));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	return (1);
}
