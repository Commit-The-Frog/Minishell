/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:19:12 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 17:04:42 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

int		ft_unset(char **argv, t_dict **env_dict)
{
	int	argc;
	int	idx;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	idx = 1;
	while (idx < argc)
	{
		del_node_with_key(env_dict, argv[idx]);
		idx++;
	}
	return (0);
}
