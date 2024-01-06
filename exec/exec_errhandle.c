/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errhandle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:23:09 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 18:38:07 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

void	exit_with_str(char *str, int custom_errno)
{
	const char	*err_msg = strerror(errno);

	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	if (custom_errno == 0)
		exit(errno);
	else
		exit(custom_errno);
}

void	exit_custom_err(char *cmd, char *str, char *err_msg, int custom_errno)
{
	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	if (custom_errno == 0)
		exit(errno);
	else
		exit(custom_errno);
}

int	print_custom_err(char *cmd, char *str, char *err_msg, int custom_errno)
{
	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, ": ", 2);
	}
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	return (custom_errno);
}
