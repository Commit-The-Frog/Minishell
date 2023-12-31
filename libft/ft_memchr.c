/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:04:40 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/12 17:10:16 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*s_uc;
	size_t			i;

	i = 0;
	s_uc = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (s_uc[i] == uc)
			return (&s_uc[i]);
		i++;
	}
	return (0);
}
