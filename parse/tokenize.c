/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:53:35 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/08 20:09:23 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			end++;
			while (str[end] && is_quote(str, end) != quote)
				end++;
		}
		else if (str[end] == ' ')
		{
			make_token(list, str, start, end);
			start = end + 1;
		}
		else if (is_double_operator(str[end], str[end + 1]))
		{
			make_token(list, str, start, end + 2);
			start = ++end + 1;
		}
		else if (is_operator(str[end + 1]) || (is_operator(str[end]) && !is_operator(str[end + 1])))
		{
			make_token(list, str, start, end + 1);
			start = end + 1;
		}
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
				quote = cur->str[i];
				i++;
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

void	remove_quote(t_token **list)
{
	t_token	*cur;
	char	*new_str;
	char	quote;
	char	*tmp;
	int		i;
	int		j;

	cur = *list;
	while (cur)
	{
		new_str = (char *)ft_calloc(ft_strlen(cur->str) + 1, sizeof(char));
		if (new_str == NULL)
			exit(EXIT_FAILURE);
		i = 0;
		j = 0;
		while (cur->str[j])
		{
			quote = is_quote(cur->str, j);
			if (quote != 0)
			{
				j++;
				while (cur->str[j] && is_quote(cur->str, j) != quote)
				{
					if (cur->str[j] == '\\' &&
					(cur->str[j + 1] == '\'' || cur->str[j + 1] == '\"'))
						j++;
					else
						new_str[i++] = cur->str[j++];
				}
			}
			else
				new_str[i++] = cur->str[j];
			j++;
		}
		tmp = cur->str;
		cur->str = new_str;
		free(tmp);
		cur = cur->next;
	}
}
