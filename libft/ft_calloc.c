/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:57:18 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/15 17:21:36 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	size_t	i;
	char	*result;

	total_size = count * size;
	i = 0;
	if (size != 0 && total_size / size != count)
		return (0);
	if (!total_size)
		total_size = 1;
	result = (char *)malloc(total_size);
	if (!result)
		return (0);
	while (i < total_size)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}
