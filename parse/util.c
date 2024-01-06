/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:31:09 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/06 18:43:52 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_quote(char *str, int	idx)
{
	if (idx == 0)
	{
		if (str[idx] == '\'' || str[idx] == '\"')
			return (str[idx]);
		else
			return (0);
	}
	else
	{
		if ((str[idx] == '\"' || str[idx] == '\'') && str[idx - 1] != '\\')
			return (str[idx]);
		else
			return (0);
	}
}