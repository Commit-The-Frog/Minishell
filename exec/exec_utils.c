/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:17:51 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:34:57 by minjacho         ###   ########.fr       */
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

int	get_proc_cnt(t_pipe_node *head)
{
	t_pipe_node	*node;
	int			size;

	size = 0;
	node = head;
	while (node)
	{
		size++;
		node = node->next_pipe;
	}
	return (size);
}

char	**get_bin_path_list(char *path)
{
	char	**path_list;
	int		idx;
	char	*tmp;

	idx = 0;
	path_list = ft_split(path, ':');
	if (!path_list)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	while (path_list[idx])
	{
		tmp = path_list[idx];
		path_list[idx] = ft_strjoin(tmp, "/");
		if (!path_list[idx])
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		free(tmp);
		idx++;
	}
	return (path_list);
}

char	*get_bin_path(char	*bin_name, t_dict **env_dict)
{
	char	*bin_path;
	t_dict	*path_node;
	char	**path_list;
	int		idx;

	path_node = get_node_with_key(*env_dict, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	path_list = get_bin_path_list(path_node->value);
	if (!path_list)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	idx = 0;
	while (path_list[idx])
	{
		bin_path = ft_strjoin(path_list[idx], bin_name);
		if (!bin_path)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		if (access(bin_path, X_OK) == 0)
			break ;
		free(bin_path);
		bin_path = NULL;
		idx++;
	}
	free_double_ptr(path_list);
	return (bin_path);
}
