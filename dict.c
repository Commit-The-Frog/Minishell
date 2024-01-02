/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:49:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 16:05:48 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

t_dict	*dict_init(char	**envp)
{
	int		idx;
	int		size;
	char	**key_value;
	t_dict	*dict;

	size = 0;
	while (envp && envp[idx])
		size++;
	dict = (t_dict *)malloc(sizeof(t_dict) * size);
	idx = 0;
	while (idx < size)
	{
		key_value = ft_split(envp[idx], '=');
		if (!key_value)
			exit(EXIT_FAILURE);
		dict[idx].key = key_value[0];
		dict[idx].value = key_value[1];
		free(key_value);
		idx++;
	}
}
