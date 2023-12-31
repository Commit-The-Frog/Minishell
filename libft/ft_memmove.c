/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:22:08 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/13 18:03:37 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_uc;
	unsigned char	*src_uc;
	size_t			i;

	if (!dst && !src)
		return (dst);
	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	i = 0;
	if (dst_uc >= src_uc && dst_uc <= src_uc + len)
	{
		i = len;
		while (i-- > 0)
			dst_uc[i] = src_uc[i];
	}
	else
	{
		while (i < len)
		{
			dst_uc[i] = src_uc[i];
			i++;
		}
	}
	return (dst);
}
