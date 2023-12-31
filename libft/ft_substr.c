/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:08:41 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/13 15:47:52 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	str_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (s_len < start)
		str_len = 0;
	else
		str_len = s_len - start;
	if (len < str_len)
		str_len = len;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < str_len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
