/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 20:43:40 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 19:48:14 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_return_str(char **return_str, char *env_name, \
						char *str_left, t_dict *env_dict)
{
	char	*str_prefix;

	if (*return_str)
		str_prefix = ft_strjoin(*return_str, \
		get_value_with_key(env_dict, env_name));
	else
		str_prefix = ft_strjoin("", get_value_with_key(env_dict, env_name));
	free(*return_str);
	if (!str_prefix)
		exit(EXIT_FAILURE);
	*return_str = ft_strjoin(str_prefix, str_left);
	if (!*return_str)
		exit(EXIT_FAILURE);
}

static char	*set_return_str(char *origin, size_t size, \
							t_dict *env_dict, char *return_str)
{
	char	*env_name;
	char	*env_value;

	env_name = ft_substr(origin, 1, get_var_len(&origin[1]));
	if (!env_name)
		exit(EXIT_FAILURE);
	env_value = get_value_with_key(env_dict, env_name);
	if (!env_value)
		env_value = "";
	ft_strlcat(return_str, env_value, size);
	return (env_name);
}

void	set_expanded_str(char *str, char *result, \
							size_t size, t_dict *env_dict)
{
	int		i;
	int		j;
	char	quote_flag;
	char	*env_name;

	i = 0;
	j = 0;
	while (str[i])
	{
		quote_flag = set_quote_flag(quote_flag, str, i);
		if (str[i] == '$' && (quote_flag == '\"' || !quote_flag) && \
		!(is_quote(str, i + 1) || str[i + 1] == ' ' || str[i + 1] == 0))
		{
			env_name = set_return_str(&str[i], size, env_dict, result);
			i += ft_strlen(env_name) + 1;
			j += get_env_length(env_name, env_dict);
			free(env_name);
		}
		else
			result[j++] = str[i++];
	}
}

void	expand_env(t_token *token, t_dict *env_dict)
{
	size_t	size;
	char	*return_str;

	if (ft_strchr(token->str, '$') == 0)
		return ;
	size = get_total_len(token->str, env_dict);
	return_str = (char *)ft_calloc(size + 1, sizeof(char));
	set_expanded_str(token->str, return_str, size, env_dict);
	free(token->str);
	token->str = return_str;
}

void	expand_var(t_token **list, t_dict *dict)
{
	t_token	*cur;
	t_token	*prev;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (prev == NULL)
		{
			if (ft_strcmp(cur->str, "$") != 0)
				expand_env(cur, dict);
		}
		else
		{
			if (ft_strcmp(cur->str, "$") != 0 && \
				prev->type != E_TYPE_REDIR_HEREDOC)
				expand_env(cur, dict);
		}
		prev = cur;
		cur = cur->next;
	}
}
