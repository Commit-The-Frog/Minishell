/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:17:58 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/05 19:44:57 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

int	check_is_valid_dir(char *path)
{
	struct stat	stat_buf;

	if (access(path, F_OK) < 0)
		return (1); // not such file or directory
	if (stat(path, &stat_buf) < 0)
		return (1); // stat error
	if (!S_ISDIR(stat_buf.st_mode))
		return (1); // not a directory
	if (access(path, X_OK) < 0)
		return (1); // Permission denied
	return (0);
}

int	ft_cd(char **argv, t_dict **env_dict)
{
	int		argc;
	t_dict	*home_dict;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	if (argc > 1)
	{
		if (check_is_valid_dir(argv[1]) != 0)
			return (1);
		if (chdir(argv[1]) < 0)
			return (1); // chdir error
	}
	else
	{
		home_dict = get_node_with_key(*env_dict, "HOME");
		if (!home_dict)
			return (1); // home variable unset error
		if (check_is_valid_dir(home_dict->value) != 0)
			return (1);
		if (chdir(home_dict->value) < 0)
			return (1); // chdir error
	}
	return (0);
}
