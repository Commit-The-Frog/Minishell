/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:17:51 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 12:09:32 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_child_state(t_pstat *pstat, int proc_cnt, int cnt, char *start_dir)
{
	int	idx;
	int	exit_stat;

	idx = 0;
	while (idx < proc_cnt)
	{
		waitpid(pstat[idx].pid, &pstat[idx].exit_stat, 0);
		idx++;
	}
	exit_stat = pstat[idx - 1].exit_stat;
	free(pstat);
	unlink_tmpfile(cnt, start_dir);
	if (WIFSIGNALED(exit_stat))
	{
		sigdelset(&recent_sig, WTERMSIG(exit_stat));
		return (WTERMSIG(exit_stat) + 128);
	}
	return (WEXITSTATUS(exit_stat));
}

int	is_path(char *str)
{
	if (ft_strncmp(str, "./", 2) == 0)
		return (1);
	if (ft_strncmp(str, "../", 3) == 0)
		return (1);
	if (ft_strncmp(str, "/", 1) == 0)
		return (1);
	return (0);
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
