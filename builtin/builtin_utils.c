/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:07:42 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/08 20:03:28 by minjacho         ###   ########.fr       */
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
	if (!cmd->argv || !cmd->argv[0])
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

int	run_builtin(t_cmd_node *cmd, t_dict **env_dict, int tmp_cnt, char *tmp_dir)
{
	int	idx;
	int	(*builtin_func)(char **, t_dict **);
	int	return_val;
	int	origin_tty[2];

	idx = 0;
	builtin_func = get_builtin_func(cmd->argv[0]);
	if (!builtin_func)
		return (-1);
	origin_tty[0] = dup(STDIN_FILENO);
	origin_tty[1] = dup(STDOUT_FILENO);
	if (!cmd->redirect)
		return_val = 0;
	else
		return_val = redirect_file(cmd->redirect, 1);
	if (return_val == 0)
		return_val = builtin_func(cmd->argv, env_dict);
	if (tmp_dir)
		unlink_tmpfile(tmp_cnt, tmp_dir);
	dup2(origin_tty[0], STDIN_FILENO);
	dup2(origin_tty[1], STDOUT_FILENO);
	close(origin_tty[0]);
	close(origin_tty[1]);
	return (return_val);
}
