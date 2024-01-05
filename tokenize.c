/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:53:35 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/05 20:13:09 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sep_by_space(t_list **list, char *str)
{
	int	start;
	int	end;
	int	quote;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"')
		{
			quote = str[end];
			end++;
			while (str[end] && str[end] != quote)
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

void	remove_quote(t_list **list)
{
	t_list	*cur;
	t_token	*tmp_token;
	char	*new_str;
	char	qoute;
	int		i;
	int		j;

	cur = *list;
	while (cur)
	{
		tmp_token = (t_token *)cur->content;
		new_str = (char *)ft_calloc(ft_strlen(tmp_token->str), sizeof(char));
		if (new_str == NULL)
			exit(EXIT_FAILURE);
		i = 0;
		j = 0;
		while (tmp_token->str[j])
		{
			if (tmp_token->str[j] == '\'' || tmp_token->str[j] == '\"')
			{
				qoute = tmp_token->str[j];
				j++;
				while (tmp_token->str[j] != qoute)
					new_str[i++] = tmp_token->str[j++];
			}
			else
				new_str[i++] = tmp_token->str[j];
			j++;
		}
		tmp_token->str = new_str;
		cur = cur->next;
	}
}
