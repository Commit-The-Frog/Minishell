/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:30:30 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 19:29:38 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*make_token(t_token **list, char *str, int start, int end)
{
	t_token		*new;
	t_token		*cur;
	char		*substr;

	if (start >= end)
		return (NULL);
	substr = ft_substr(str, start, end - start);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (substr == NULL || new == NULL)
		exit(EXIT_FAILURE);
	new->str = substr;
	new->type = get_type(new);
	if (new->type == E_TYPE_SEMICOLON)
		return (syntax_err(new->str));
	new->next = NULL;
	if (*list == NULL)
		*list = new;
	if (*list == new)
		return (NULL);
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (NULL);
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
