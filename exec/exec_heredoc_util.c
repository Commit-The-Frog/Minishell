/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:07:27 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 17:24:18 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sub_preprocess(\
	t_redir_node *redir, char *start_dir, int get_input, t_dict **dict)
{
	if (!redir)
		return ;
	if (redir->type == E_TYPE_REDIR_HEREDOC)
		redirect_heredoc(&redir->file_name, start_dir, get_input, dict);
	if (redir->next)
		heredoc_sub_preprocess(redir->next, start_dir, get_input, dict);
}

void	heredoc_preprocess(\
	t_pipe_node *head, char *start_dir, int get_input, t_dict **dict)
{
	if (head->cmd)
		heredoc_sub_preprocess(head->cmd->redirect, start_dir, get_input, dict);
	if (head->next_pipe)
		heredoc_preprocess(head->next_pipe, start_dir, get_input, dict);
}

static void	heredoc_set_expanded_str(char *str, char *result, \
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
		if (str[i] == '$' && \
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

static size_t	heredoc_get_total_len(char *str, t_dict *env_dict)
{
	size_t	size;
	size_t	idx;
	char	quote_flag;
	char	*env_name;

	quote_flag = 0;
	idx = 0;
	size = 0;
	while (idx < ft_strlen(str))
	{
		quote_flag = set_quote_flag(quote_flag, str, idx);
		if (str[idx] == '$' && \
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
		idx++;
	}
	return (size);
}

char	*heredoc_expand_str(char *origin, t_dict *env_dict)
{
	size_t	size;
	char	*return_str;

	size = heredoc_get_total_len(origin, env_dict);
	return_str = (char *)ft_calloc(size + 1, sizeof(char));
	heredoc_set_expanded_str(origin, return_str, size, env_dict);
	return (return_str);
}
