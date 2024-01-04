/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:03:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 17:01:54 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

static void	print_export(char **envp)
{
	const char	*prefix="declare -x ";
	int			i;
	int			j;
	int			has_assign;

	i = -1;
	while (envp[++i])
	{
		has_assign = 0;
		write(STDOUT_FILENO, prefix, ft_strlen(prefix));
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

static void	sort_print_env(t_dict *env_dict)
{
	char	**envp;
	char	*tmp;
	int		i;
	int		j;

	envp = generate_envp(env_dict);
	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_export(envp);
	free_double_ptr(envp);
}

int	 ft_export(char **argv, t_dict **env_dict)
{
	int	argc;
	int	idx;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	idx = 1;
	while (idx < argc)
	{
		add_node_back(env_dict, argv[idx]);
		idx++;
	}
	if (argc == 1)
		sort_print_env(*env_dict);
	return (0);
}
