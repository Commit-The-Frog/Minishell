/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:47:43 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 17:59:12 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_nl_opt(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **argv, t_dict **env_dict)
{
	int	argc;
	int	n_flag;
	int	idx;

	argc = 0;
	n_flag = 0;
	idx = 0;
	env_dict = NULL;
	while (argv[argc])
		argc++;
	while (++idx < argc)
	{
		if (is_nl_opt(argv[idx]) && (idx == 1 || is_nl_opt(argv[idx - 1])))
		{
			n_flag = 1;
			continue ;
		}
		write(STDOUT_FILENO, argv[idx], ft_strlen(argv[idx]));
		if (idx != argc - 1)
			write(STDOUT_FILENO, " ", 1);
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
