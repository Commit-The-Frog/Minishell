/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:50:07 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:30:42 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;

	result = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, (char *)s1, ft_strlen(s1) + 1);
	return (result);
}

char	*ft_strcdup(const char *s1, int c)
{
	char	*result;
	size_t	len;
	size_t	idx;

	len = 0;
	idx = 0;
	while (s1[len] && s1[len] != (char)c)
		len++;
	if (!s1[len])
		len--;
	result = (char *)malloc((len + 2) * sizeof(char));
	if (!result)
		return (NULL);
	while (idx < len + 1)
	{
		result[idx] = s1[idx];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}
