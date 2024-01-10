/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:37:06 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 19:29:17 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_total_len(char *str, t_dict *env_dict)
{
	size_t	size;
	int		idx;
	char	quote_flag;
	char	*env_name;

	quote_flag = 0;
	idx = -1;
	size = 0;
	while (++idx < ft_strlen(str))
	{
		quote_flag = set_quote_flag(quote_flag, str, idx);
		if (str[idx] == '$' && (quote_flag == '\"' || !quote_flag) && \
		!(is_quote(str, idx + 1) || str[idx + 1] == ' ' || str[idx + 1] == 0))
		{
			env_name = ft_substr(str, idx + 1, get_var_len(&str[idx + 1]));
			if (!env_name)
				exit(EXIT_FAILURE);
			size += get_env_length(env_name, env_dict);
			idx += ft_strlen(env_name);
			free(env_name);
		}
		size++;
	}
	return (size);
}

size_t	get_var_len(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (idx == 0)
		{
			if (!(str[idx] == '_' || ft_isalpha(str[idx])))
				return (1);
		}
		else
		{
			if (!(str[idx] == '_' || ft_isalnum(str[idx])))
				return (idx);
		}
		idx++;
	}
	return (idx);
}

size_t	get_env_length(char *env_name, t_dict *env_dict)
{
	char	*value;

	value = get_value_with_key(env_dict, env_name);
	if (!value)
		return (0);
	else
	{
		return (ft_strlen(value));
	}
}

void	remove_empty_token(t_token **list)
{
	t_token	*cur;
	t_token	*tmp;
	t_token	*prev;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (cur->str == NULL || cur->str[0] == '\0')
		{
			if (prev == NULL)
				*list = cur->next;
			else
				prev->next = cur->next;
			free(cur->str);
			free(cur);
			if (prev == NULL)
				cur = *list;
			else
				cur = prev->next;
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
}

char	set_quote_flag(char quote_flag, char *str, int idx)
{
	char	return_flag;

	if ((str[idx] == '\"' || str[idx] == '\'') \
		&& (idx == 0 || str[idx - 1] != '\\'))
	{
		if (!quote_flag)
			return_flag = str[idx];
		else if (quote_flag == str[idx])
			return_flag = 0;
	}
	else
		return_flag = quote_flag;
	return (return_flag);
}
