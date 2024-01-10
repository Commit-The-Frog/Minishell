/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:12:54 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 22:18:30 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous(t_token **list, char *str)
{
	t_token	*cur;
	t_token	*prev;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (prev && (prev->type == 5 || prev->type == 7 || prev->type == 8) \
			&& ft_strlen(cur->str) == 0)
		{
			ambiguous_err(cur->origin);
			free_token_list(list);
			return (-1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int	check_unexpected_token(t_token **list)
{
	t_token	*cur;
	t_token	*prev;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (cur->type == E_TYPE_SEMICOLON || cur->type == E_TYPE_AMPERSAND || \
			cur->type == E_TYPE_DOUBLE_AMPERSAND || \
			cur->type == E_TYPE_DOUBLE_PIPE)
		{
			syntax_err(cur->str, NULL);
			return (-1);
		}
		if (prev && prev->type >= 5 && prev->type <= 8 \
			&& (cur->type >= 5 && cur->type <= 8))
		{
			syntax_err(cur->str, NULL);
			return (-1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}
