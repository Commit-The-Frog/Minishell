/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:53:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/11 14:27:12 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(char *str, t_dict *dict, t_pipe_node **ast)
{
	t_token		*token_list;
	char		quote;
	int			err_flag;

	err_flag = 0;
	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	token_list = NULL;
	*ast = NULL;
	quote = check_quote(str);
	if (quote != 0)
	{
		quote_err(quote);
		return (-1);
	}
	if (tokenize(&token_list, str, dict) == -1)
		err_flag = -1;
	get_ast(ast, &token_list, err_flag);
	return (err_flag);
}
