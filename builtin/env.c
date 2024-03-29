/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:18:01 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 17:25:40 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **envp)
{
	int	i;
	int	j;
	int	has_assign;

	i = -1;
	while (envp[++i])
	{
		has_assign = 0;
		j = 0;
		if (ft_strncmp(envp[i], "?", 1) == 0)
			continue ;
		if (!ft_strchr(envp[i], '='))
			continue ;
		while (envp[i][j])
		{
			write(STDOUT_FILENO, &envp[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

int	ft_env(char **argv, t_dict **env_dict)
{
	int		argc;
	char	**envp;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	envp = generate_envp(*env_dict);
	print_env(envp);
	free_double_ptr(envp);
	return (0);
}
