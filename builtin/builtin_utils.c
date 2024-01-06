/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:07:42 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:52:45 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*get_builtin_func(char *func)
{
	if (ft_strcmp(func, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(func, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(func, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(func, "export") == 0)
		return (ft_export);
	if (ft_strcmp(func, "unset") == 0)
		return (ft_unset);
	if (ft_strcmp(func, "env") == 0)
		return (ft_env);
	if (ft_strcmp(func, "exit") == 0)
		return (ft_exit);
	return (NULL);
}

int	is_builtin_cmd(t_cmd_node *cmd)
{
	if (!cmd)
		return (0);
	if (!cmd->argv)
		return (0);
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin_cmds(char **argv, t_dict **env_dict)
{
	int	idx;
	int	(*builtin_func)(char **, t_dict **);
	int	return_val;

	idx = 0;
	builtin_func = get_builtin_func(argv[0]);
	if (!builtin_func)
		return (-1);
	return_val = builtin_func(argv, env_dict);
	return (return_val);
}
