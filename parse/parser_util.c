/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:37:16 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 16:38:37 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_argv_array(t_simple_cmd_node *list, char **arr)
{
	t_simple_cmd_node	*cur;
	char				**tmp_arr;
	int					i;
	int					j;

	cur = list;
	i = 0;
	while (cur)
	{
		arr[i++] = ft_strdup(cur->argv);
		cur = cur->next;
	}
}

char	**conv_list_to_array(t_simple_cmd_node *list)
{
	t_simple_cmd_node	*cur;
	int					count;
	char				**arr;

	cur = list;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	arr = (char **)ft_calloc(count + 1, sizeof(char *));
	if (arr == NULL)
		exit(EXIT_FAILURE);
	get_argv_array(list, arr);
	return (arr);
}
