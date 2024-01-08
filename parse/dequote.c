/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:58:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/08 20:12:54 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_quote(char *str)
{
	int		i;
	char	quote;
	
	i = 0;
	while (str[i])
	{
		quote = is_quote(str, i);
		if (quote != 0)
		{
			i++;
			while (str[i] && is_quote(str, i) != quote)
				i++;
			if (str[i] == 0)
				return (quote);
		}
		i++;
	}
	return (0);
}

// void	get_more_input(char **origin)
// {
// 	char	*buff;
// 	char	*joined_str;

// 	while (!check_quote(*origin))
// 	{
// 		buff = readline("> ");
// 		joined_str = ft_strjoin(*origin, buff);
// 		free(*origin);
// 		free(buff);
// 		*origin = joined_str;
// 	}
// }

t_pipe_node	*parse(char *str, t_dict *dict)
{
	t_token		*token_list;
	t_token		*cur;
	t_pipe_node	*ast;
	char		quote;

	if (str == NULL || ft_strlen(str) == 0)
		return (NULL);
	token_list = NULL;
	ast = NULL;
	quote = check_quote(str);
	if (quote != 0)
	{
		quote_err(quote);
		return (NULL);
	}
	tokenize(&token_list, str, dict);
	get_ast(&ast, &token_list);
	return (ast);
}

/*
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
}*/
