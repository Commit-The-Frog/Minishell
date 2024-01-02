/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:30:30 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/02 21:53:51 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_minishell.h"

char	is_operator(char c)
{
	const char	*control_operator[9] = {"|", "&", ";", "(", ")", "<", ">", "<<", ">>"};
	int			i;

	i = 0;
	while (i < 9)
	{
		if (ft_strlen(control_operator[i]) == 1)
		{
			if (control_operator[i][0] == c)
				return (1);
		}
		else
		{
			if (ft_strchr(control_operator[i], c) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_comb_operator(char c1, char c2)
{
	const char	*control_operator_double[2] = {"<<", ">>"};
	int			i;
	
	i = 0;
	while (i < 2)
	{
		if (c1 == control_operator_double[i][0] && c2 == control_operator_double[i][1] || \
			c2 == control_operator_double[i][1] && c1 == control_operator_double[i][0])
			return (1);
		i++;
	}
	return (0);
}

void	make_token(t_list **list, char *str, int start, int end)
{
	t_list	*token;
	char	*substr;

	substr = ft_substr(str, start, end - start);
	if (str == NULL)
		exit(EXIT_FAILURE);
	token = ft_lstnew((void *)substr);
	if (token == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, token);
}

void	tokenize(t_list **list, char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (end >= 1 && !is_operator(str[end]) && is_operator(str[end - 1]))
		{
			make_token(list, str, start, end);
			start = end;
		}
		if (end >= 1 && is_operator(str[end]) && !is_operator(str[end - 1]))
		{
			make_token(list, str, start, end);
			start = end;
		}
		else if (end >= 1 && is_operator(str[end]) && !is_comb_operator(str[end], str[end - 1]))
		{
			make_token(list, str, start, end);
			start = end;
		}
		else if (end >=1 && is_comb_operator(str[end], str[end - 1]))
		{
			make_token(list, str, start, ++end);
			start = end;
		}
		else if (str[end] == '#')
			break;
		else if (str[end] == '\'')
		{
			make_token(list, str, start, end);
			start = end;
			end++;
			while (str[end] && str[end] != '\'')
				end++;
			make_token(list, str, start + 1, end);
			start = end + 1;
		}
		else if (str[end] == '\"')
		{
			make_token(list, str, start, end);
			start = end;
			end++;
			while (str[end] && str[end] != '\"')
				end++;
			make_token(list, str, start + 1, end);
			start = end + 1;
		}
		else if (str[end] == ' ')
		{
			if (end >= 1 && str[end - 1] != '\'' && str[end - 1] != '\"' && str[end - 1] != ' ')
				make_token(list, str, start, end);
			start = end + 1;
		}
		end++;
	}
	make_token(list, str, start, end);
}
