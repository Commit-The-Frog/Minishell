/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:23:11 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/10 22:47:21 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*quote_err(char c)
{
	write(2, "minishell: unexpected EOF while looking for matching `", 55);
	write(2, &c, 1);
	write(2, "\'\nminishell: syntax error: unexpected end of file\n", 51);
	return (NULL);
}

void	*syntax_err(char *str)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	return (NULL);
}

void	*ambiguous_err(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ambiguous redirect\n", 21);
	return (NULL);
}
