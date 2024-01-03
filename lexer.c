/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:30:30 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/03 14:29:51 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	const char	*control_operator_double[4] = {"<<", ">>", "||", "&&"};
	int			i;
	
	i = 0;
	while (i < 4)
	{
		if (c1 == control_operator_double[i][0] && c2 == control_operator_double[i][1] || \
			c2 == control_operator_double[i][1] && c1 == control_operator_double[i][0])
			return (1);
		i++;
	}
	return (0);
}

int	get_type(t_token *token)
{
	char	*str;

	str = token->str;
	if (ft_strlen(str) == 1 && !ft_strncmp(str, "|", 1))
		return (E_TYPE_PIPE);
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, "&", 1))
		return (E_TYPE_AMPERSAND);
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, ";", 1))
		return (E_TYPE_SEMICOLON);
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, "<", 1))
		return (E_TYPE_REDIR_LEFT);
	else if (ft_strlen(str) == 1 && !ft_strncmp(str, ">", 1))
		return (E_TYPE_REDIR_RIGHT);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, ">>", 2))
		return (E_TYPE_REDIR_APPEND);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "<<", 2))
		return (E_TYPE_REDIR_HEREDOC);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "&&", 2))
		return (E_TYPE_DOUBLE_AMPERSAND);
	else if (ft_strlen(str) == 2 && !ft_strncmp(str, "||", 2))
		return (E_TYPE_DOUBLE_PIPE);
	else
		return (E_TYPE_SIMPLE_CMD);
}

void	make_token(t_list **list, char *str, int start, int end)
{
	t_token			*token;
	t_list			*new;
	char			*substr;

	substr = ft_substr(str, start, end - start);
	if (str == NULL)
		exit(EXIT_FAILURE);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		exit(EXIT_FAILURE);
	token->str = substr;
	token->type = get_type(token);
	new = ft_lstnew((void *)token);
	if (new == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, new);
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
			start = end;
		}
		end++;
	}
	make_token(list, str, start, end);
}
