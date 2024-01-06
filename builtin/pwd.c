/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:58:39 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 18:37:50 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

int	ft_pwd(char **argv, t_dict **env_dict)
{
	char	*cur_dir;

	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, 0);
	if (!cur_dir)
		print_custom_err("pwd", NULL, strerror(errno), 1);
	write(STDIN_FILENO, cur_dir, ft_strlen(cur_dir));
	write(STDIN_FILENO, "\n", 1);
	free(cur_dir);
	return (0);
}
