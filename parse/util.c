/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:31:09 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 21:00:46 by junkim2          ###   ########.fr       */
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

char	*expand_str(char *origin, t_dict *env_dict)
{
	size_t	size;
	char	*return_str;

	size = get_total_len(origin, env_dict);
	return_str = (char *)ft_calloc(size + 1, sizeof(char));
	set_expanded_str(origin, return_str, size, env_dict);
	return (return_str);
}

void	token_list_printer(t_token *token_list)
{
	t_token	*cur;

	cur = token_list;
	while (cur)
	{
		printf("[%s|%u] ", cur->str, (unsigned int)cur->type);
		cur = cur->next;
	}
	printf("\n");
}

void	ast_printer(t_pipe_node *ast)
{
	t_pipe_node			*cur;
	t_cmd_node			*cur_cmd;
	t_redir_node		*cur_redir;
	t_simple_cmd_node	*cur_scmd;
	int					i;

	cur = ast;
	printf("<ast_printer start>\n");
	while (cur)
	{
		cur_cmd = cur->cmd;
		cur_redir = cur_cmd->redirect;
		cur_scmd = cur_cmd->simple_cmd;
		printf("====redirects====\n");
		while (cur_redir)
		{
			printf("%u, %s\n", (unsigned int)cur_redir->type, \
			cur_redir->file_name);
			cur_redir = cur_redir->next;
		}
		printf("====simple cmd====\n");
		while (cur_scmd)
		{
			printf("[%s] ", cur_scmd->argv);
			cur_scmd = cur_scmd->next;
		}
		printf("\n====argv====\n");
		i = 0;
		while (cur_cmd->argv[i])
		{
			printf("[%s] ", cur_cmd->argv[i++]);
		}
		printf("\n");
		cur = cur->next_pipe;
	}
}
