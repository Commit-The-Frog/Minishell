/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:31:09 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 14:04:04 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	is_operator(char c)
{
	int			i;
	const char	*control_operator[9] = {"|", "&", ";", "(", ")", \
										"<", ">", "<<", ">>"};

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

int	is_double_operator(char c1, char c2)
{
	const char	*control_operator_double[4] = {"<<", ">>", "||", "&&"};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (c1 == control_operator_double[i][0] && \
			c2 == control_operator_double[i][1] || \
			c2 == control_operator_double[i][1] && \
			c1 == control_operator_double[i][0])
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
	else if (ft_strchr(str, '$'))
		return (E_TYPE_EXPAND);
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
