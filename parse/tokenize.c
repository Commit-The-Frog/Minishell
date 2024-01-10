/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:53:35 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 20:10:55 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_token_and_move(t_token **list, char *str, int *start, int end)
{
	if (str[end] == ' ')
	{
		make_token(list, str, *start, end);
		*start = end + 1;
	}
	else if (is_operator(str[end + 1]) || (is_operator(str[end]) \
			&& !is_operator(str[end + 1])))
	{
		make_token(list, str, *start, end + 1);
		*start = end + 1;
	}
}

static void	move_until_quote(char *str, int *end, char quote)
{
	(*end)++;
	while (str[*end] && is_quote(str, *end) != quote)
		(*end)++;
}

void	sep_token(t_token **list, char *str)
{
	int	start;
	int	end;
	int	quote;

	start = 0;
	end = 0;
	while (str[end])
	{
		quote = is_quote(str, end);
		if (quote != 0)
			move_until_quote(str, &end, quote);
		else if (is_double_operator(str[end], str[end + 1]))
		{
			make_token(list, str, start, end + 2);
			start = ++end + 1;
		}
		else
			make_token_and_move(list, str, &start, end);
		end++;
	}
	make_token(list, str, start, end);
}

void	split_token(t_token **list)
{
	t_token	*cur;
	int		i;
	char	quote;

	cur = *list;
	while (cur)
	{
		i = 0;
		while (cur->str[i])
		{
			if (cur->str[i] == '\'' || cur->str[i] == '\"')
			{
				quote = cur->str[i++];
				while (cur->str[i] && cur->str[i] != quote)
					i++;
			}
			if (cur->str[i] == ' ')
			{
				insert_token(&cur, cur->str, ++i);
				break ;
			}
			i++;
		}
		cur = cur->next;
	}
}
