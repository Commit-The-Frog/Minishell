/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:17:51 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 21:42:09 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

void	free_double_ptr(char **lists)
{
	int	idx;

	idx = 0;
	while (lists[idx])
	{
		free(lists[idx]);
		idx++;
	}
	free(lists);
}
