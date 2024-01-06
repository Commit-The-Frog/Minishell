/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:47:43 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/05 15:29:08 by minjacho         ###   ########.fr       */
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
		write(STDOUT_FILENO, argv[idx], ft_strlen(argv[idx]));
		if (idx != argc - 1)
			write(STDOUT_FILENO, " ", 1);
		idx++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
