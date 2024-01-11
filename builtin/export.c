/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:03:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 14:38:07 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	envp_printer(char *env)
{
	int	has_assign;
	int	i;

	has_assign = 0;
	i = 0;
	while (env[i])
	{
		if (env[i] == '\"')
			write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, &env[i], 1);
		if (env[i] == '=')
		{
			has_assign = 1;
			write(STDOUT_FILENO, "\"", 1);
		}
		i++;
	}
	if (has_assign)
		write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_export(char **envp)
{
	int	i;
	int	has_assign;

	i = 0;
	while (envp[i])
	{
		has_assign = 0;
		if (ft_strncmp(envp[i], "?", 1) == 0)
		{
			i++;
			continue ;
		}
		envp_printer(envp[i]);
		i++;
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

static int	is_valid_id(char *s)
{
	int	i;
	int	after_assign;

	i = 0;
	after_assign = 0;
	while (s[i])
	{
		if (i == 0)
		{
			if (!(ft_isalpha(s[i]) || s[i] == '_'))
				return (0);
		}
		else
		{
			if (s[i] == '=')
				after_assign = 1;
			if (!after_assign)
			{
				if (!(ft_isalpha(s[i]) || s[i] == '_' || ft_isdigit(s[i])))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_export(char **argv, t_dict **env_dict)
{
	int	argc;
	int	idx;
	int	result;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	idx = 1;
	result = 0;
	while (idx < argc)
	{
		if (is_valid_id(argv[idx]))
		{
			add_node_back(env_dict, argv[idx]);
		}
		else
			result = invalid_id_err("export: ", argv[idx]);
		idx++;
	}
	if (argc == 1)
		sort_print_env(*env_dict);
	return (result);
}
