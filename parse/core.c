/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:53:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 20:39:14 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	> This is core function of parse part
	This function analyze syntax and shell grammer,
	returns abstract syntax tree -> [t_pipe_node *ast]
	* if error occurs, returns NULL
*/
t_pipe_node	*parse(char *str, t_dict *dict)
{
	t_token		*token_list;
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
	if (tokenize(&token_list, str, dict) == -1)
		return (NULL);
	get_ast(&ast, &token_list);
	return (ast);
}
