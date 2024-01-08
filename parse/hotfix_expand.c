/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotfix_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:43:40 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/08 18:02:19 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	set_quote_flag(char quote_flag, char *str, int idx)
{
	char	return_flag;

	if ((str[idx] == '\"' || str[idx] == '\'') && (idx == 0 || str[idx - 1] != '\\'))
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

static size_t	get_var_len(char *str)
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
			if(!(str[idx] == '_' || ft_isalnum(str[idx])))
				return (idx);
		}
		idx++;
	}
	return (idx);
}

void	update_return_str(char **return_str, char *env_name, char *str_left, t_dict *env_dict)
{
	char	*str_prefix;

	if (*return_str)
		str_prefix = ft_strjoin(*return_str, get_value_with_key(env_dict, env_name));
	else
		str_prefix = ft_strjoin("", get_value_with_key(env_dict, env_name));
	free(*return_str);
	if (!str_prefix)
		exit(EXIT_FAILURE);
	*return_str = ft_strjoin(str_prefix, str_left);
	if (!*return_str)
		exit(EXIT_FAILURE);
}

static size_t	get_env_length(char *env_name, t_dict *env_dict)
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

static size_t	get_total_len(char *str, t_dict *env_dict)
{
	size_t	size;
	int		idx;
	char	quote_flag;
	char	*env_name;
	size_t	str_len;

	str_len = ft_strlen(str);
	quote_flag = 0;
	idx = 0;
	size = 0;
	while (idx < str_len)
	{
		quote_flag = set_quote_flag(quote_flag, str, idx);
		if (str[idx] == '$' && (quote_flag == '\"' || !quote_flag))
		{
			env_name = ft_substr(str, idx + 1, get_var_len(&str[idx + 1]));
			if (!env_name)
				exit(EXIT_FAILURE); // malloc error
			size += get_env_length(env_name, env_dict);
			idx += ft_strlen(env_name);
		}
		size++;
		idx++;
	}
	return (size);
}

void	expand_env(t_token *token, t_dict *env_dict)
{
	size_t	size;
	int		idx;
	int		sub_idx;
	char	quote_flag;
	char	*env_name;
	char	*return_str;
	char	*str;
	char	*env_value;

	if (ft_strchr(token->str, '$') == 0)
		return ;
	quote_flag = 0;
	size = get_total_len(token->str, env_dict);
	// printf("%d\n", size);
	return_str = (char *)ft_calloc(size + 1, sizeof(char));
	str = token->str;
	idx = 0;
	sub_idx = 0;
	while (str[idx])
	{
		quote_flag = set_quote_flag(quote_flag, str, idx);
		if (str[idx] == '$' && (quote_flag == '\"' || !quote_flag))
		{
			env_name = ft_substr(str, idx + 1, get_var_len(&str[idx + 1]));
			if (!env_name)
				exit(EXIT_FAILURE); // malloc error
			env_value = get_value_with_key(env_dict, env_name);
			if (!env_value)
				env_value = "";
			ft_strlcat(return_str, env_value, size);
			idx += ft_strlen(env_name) + 1;
			sub_idx += get_env_length(env_name, env_dict);
		}
		else
		{
			return_str[sub_idx] = str[idx];
			sub_idx++;
			idx++;
		}
	}
	// printf("%s\n", return_str);
	token->str = return_str;
}
