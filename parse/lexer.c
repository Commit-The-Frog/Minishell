/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:30:30 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/08 20:59:41 by junkim2          ###   ########.fr       */
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

int	is_double_operator(char c1, char c2)
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

void	make_token(t_token **list, char *str, int start, int end)
{
	t_token		*new;
	t_token		*cur;
	char		*substr;

	if (start >= end)
		return ;
	substr = ft_substr(str, start, end - start);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->str = substr;
	new->type = get_type(new);
	if (new->type == E_TYPE_SEMICOLON)
	{
		syntax_err(new->str);
		return ;
	}
	new->next = NULL;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	insert_token(t_token **list, char *str, int start)
{
	t_token		*new;
	t_token		*tmp;
	char		*substr;
	int			end;
	char		*tmp_str;

	end = ft_strlen(str);
	substr = ft_substr(str, start, end - start);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	// printf("\033[31m");
	// printf("%d %d\n", start, end);
	// printf("sub:%s\n", substr);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		exit(EXIT_FAILURE);
	new->str = substr;
	new->type = E_TYPE_SIMPLE_CMD;
	tmp = (*list)->next;
	(*list)->next = new;
	new->next = tmp;
	substr = ft_substr(str, 0, start - 1);
	if (substr == NULL)
		exit(EXIT_FAILURE);
	// printf("%d %d\n", start, end);
	// printf("sub:%s\n", substr);
	// printf("\033[0m");
	tmp_str = (*list)->str;
	(*list)->str = substr;
	free(tmp_str);
}

void	tokenize(t_token **list, char *str, t_dict *dict)
{
	sep_token(list, str);
	expand_var(list, dict);
	split_token(list);
	remove_quote(list);
	remove_empty_token(list);
	// token_list_printer(*list);
}
