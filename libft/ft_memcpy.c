/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:16:09 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/13 18:03:24 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_uc;
	unsigned char	*src_uc;
	size_t			i;

	if (!dst && !src)
		return (dst);
	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_uc[i] = src_uc[i];
		i++;
	}
	return (dst);
}
