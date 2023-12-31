/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:29:49 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/13 17:39:12 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_member(char const *set, char c)
{
	size_t	i;

	i = 0;
	if (!set)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	trim_strcpy(char *str, char const *s1, int s1_start, size_t str_len)
{
	size_t	i;

	i = 0;
	while (i < str_len)
	{
		str[i] = s1[s1_start];
		s1_start++;
		i++;
	}
	str[i] = '\0';
	return ;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	i_end;
	size_t	str_len;
	char	*str;

	i = 0;
	i_end = ft_strlen(s1);
	if (i_end == 0)
		str_len = 0;
	else
	{
		i_end--;
		while (i <= i_end && is_member(set, s1[i]))
			i++;
		while (i <= i_end && is_member(set, s1[i_end]))
			i_end--;
		str_len = i_end - i + 1;
	}
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (0);
	trim_strcpy(str, s1, i, str_len);
	return (str);
}
