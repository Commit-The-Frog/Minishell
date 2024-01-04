/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:18:01 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 16:53:04 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

static void	print_env(char **envp)
{
	int			i;
	int			j;
	int			has_assign;

	i = -1;
	while (envp[++i])
	{
		has_assign = 0;
		j = 0;
		while (envp[i][j])
		{
			write(STDOUT_FILENO, &envp[i][j], 1);
			if (envp[i][j] == '=')
			{
				has_assign = 1;
				write(STDOUT_FILENO, "\"", 1);
			}
			j++;
		}
		if (has_assign)
			write(STDOUT_FILENO, "\"", 1);
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	ft_env(char **argv, t_dict **env_dict)
{
	int		argc;
	int		idx;
	char	**envp;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	envp = generate_envp(*env_dict);
	print_env(envp);
	free_double_ptr(envp);
	return (0);
}
