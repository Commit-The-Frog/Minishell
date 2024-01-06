/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:06 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/06 21:34:37 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(t_token **list, t_dict *dict)
{
	t_token	*cur;
	char	*substr;
	char	*var;
	char	*tmp;
	int		i;

	cur = *list;
	while (cur)
	{
		if (ft_strchr(cur->str, '$') != 0)
		{
			// printf("%s\n", cur->str);
			i = 0;
			if (cur->str[i] == '$')
				i++;
			substr = ft_substr(cur->str, i, ft_strlen(cur->str) - i);
			var = get_value_with_key(dict, substr);
			free(substr);
			if (var == NULL)
			{
				cur = cur->next;
				continue ;
			}
			tmp = cur->str;
			cur->str = var;
			free(tmp);
		}
		cur = cur->next;
	}
}
