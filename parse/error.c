/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:23:11 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/06 18:48:37 by junkim2          ###   ########.fr       */
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
