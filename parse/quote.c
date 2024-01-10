/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:58:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 17:09:17 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_quote(char *str, int idx)
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

char	check_quote(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		quote = is_quote(str, i);
		if (quote != 0)
		{
			i++;
			while (str[i] && is_quote(str, i) != quote)
				i++;
			if (str[i] == 0)
				return (quote);
		}
		i++;
	}
	return (0);
}

static void	set_str_without_quote(char *new_str, char *origin)
{
	int		i;
	int		j;
	char	quote;

	j = 0;
	while (origin[j])
	{
		quote = is_quote(origin, j);
		if (quote != 0)
		{
			j++;
			while (origin[j] && is_quote(origin, j) != quote)
			{
				if (origin[j] == '\\' && \
				(origin[j + 1] == '\'' || origin[j + 1] == '\"'))
					j++;
				else
					new_str[i++] = origin[j++];
			}
		}
		else
			new_str[i++] = origin[j];
		j++;
	}
}

void	remove_quote(t_token **list)
{
	t_token	*cur;
	t_token	*prev;
	char	*new_str;
	char	*tmp;
	int		i;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (prev == NULL || prev->type != E_TYPE_REDIR_HEREDOC)
		{
			new_str = (char *)ft_calloc(ft_strlen(cur->str) + 1, sizeof(char));
			if (new_str == NULL)
				exit(EXIT_FAILURE);
			i = 0;
			set_str_without_quote(new_str, cur->str);
			tmp = cur->str;
			cur->str = new_str;
			free(tmp);
		}
		prev = cur;
		cur = cur->next;
	}
}
