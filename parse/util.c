/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:31:09 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/08 20:13:28 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_quote(char *str, int	idx)
{
	if (idx == 0)
	{
		if (str[idx] == '\'' || str[idx] == '\"')
			return (str[idx]);
		else
			return (0);
	}
	else
	{
		if ((str[idx] == '\"' || str[idx] == '\'') && str[idx - 1] != '\\')
			return (str[idx]);
		else
			return (0);
	}
}

int	count_word(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
		{
			count++;
			while (str[i] && str[i] != ' ')
				i++;
		}
		if (str[i] == 0)
			break ;
		i++;
	}
	return (count);
}

void	token_list_printer(t_token *token_list)
{
	t_token	*cur;

	// ======print=======
	cur = token_list;
	while (cur)
	{
		printf("[%s|%u] ", cur->str, (unsigned int)cur->type);
		cur = cur->next;
	}
	printf("\n");
	// ==================
}
