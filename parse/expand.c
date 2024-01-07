/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:06 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/07 18:59:30 by minjacho         ###   ########.fr       */
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
			i = 0;
			if (cur->str[i] == '$')
				i++;
			substr = ft_substr(cur->str, i, ft_strlen(cur->str) - i);
			var = get_value_with_key(dict, substr);
			free(substr);
			tmp = cur->str;
			cur->str = ft_strdup(var);
			free(tmp);
		}
		cur = cur->next;
	}
}

void	remove_empty_token(t_token **list)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *list;
	if (cur->str == NULL)
		*list = NULL;
	while (cur)
	{
		if (cur->next && cur->next->str == NULL)
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			free(tmp->str);
			free(tmp);
		}
		cur = cur->next;
	}
}
