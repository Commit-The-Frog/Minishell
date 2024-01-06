/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:58:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/06 12:28:32 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == 0)
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

void	get_more_input(char **origin)
{
	char	*buff;
	char	*joined_str;

	while (!check_quote(*origin))
	{
		buff = readline("> ");
		joined_str = ft_strjoin(*origin, buff);
		free(*origin);
		free(buff);
		*origin = joined_str;
	}
}

void	check_leak(void)
{
	system("leaks a.out");
}

int	main(void)
{
	char		*origin;
	t_token		*token_list;
	t_token		*cur;
	t_pipe_node	*ast;
	t_cmd_node	*cur_cmd;

	// atexit(check_leak);
	token_list = NULL;
	print_logo();
	origin = readline("minishell> ");
	get_more_input(&origin);
	tokenize(&token_list, origin);
	cur = token_list;
	while (cur)
	{
		if (cur->str != NULL)
			printf("[%s|%u] ", cur->str, (unsigned int)cur->type);
		cur = cur->next;
	}
	printf("\n");
	get_ast(&ast, &token_list);
	cur_cmd = ast->cmd;
	// while (cur_cmd)
	// {
	// 	t_redir_node *cur_redir = cur_cmd->redirect;
	// 	while (cur_redir)
	// 	{
	// 		t_redir_node *tmp = cur_redir;
			
	// 	}
	// }
	free(origin);
}
