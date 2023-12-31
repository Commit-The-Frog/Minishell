/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:22:41 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:28:31 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*string;

	i = 0;
	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!string)
		return (0);
	while (i < s1_len + s2_len)
	{
		if (i < s1_len)
			string[i] = s1[i];
		else
			string[i] = s2[i - s1_len];
		i++;
	}
	string[i] = '\0';
	return (string);
}
