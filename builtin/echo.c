/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:47:43 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 15:14:41 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

int	ft_echo(char **argv, t_dict **env_dict)
{
	int	argc;
	int	n_flag;
	int	idx;

	argc = 0;
	n_flag = 0;
	idx = 1;
	while (argv[argc])
		argc++;
	if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
		n_flag = 1;
	if (n_flag)
		idx++;
	while (idx < argc)
	{
		write(STDIN_FILENO, argv[idx], ft_strlen(argv[idx]));
		idx++;
	}
	if (!n_flag)
		write(STDIN_FILENO, "\n", 1);
	return (0);
}
