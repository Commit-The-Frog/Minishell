/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:14:43 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/14 12:42:47 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**return_with_free(char **res, char *origin, size_t res_i)
{
	size_t	idx;

	idx = 0;
	if (origin)
	{
		free(origin);
		origin = NULL;
	}
	if (res)
	{
		while (idx < res_i)
		{
			if (res[idx])
			{
				free(res[idx]);
				res[idx] = NULL;
			}
			idx++;
		}
		free(res);
		res = NULL;
	}
	return (0);
}

static char	**sub_split(char **res, char *origin, size_t s_len)
{
	size_t	res_i;
	size_t	s_i;

	res_i = 0;
	s_i = 0;
	while (s_i < s_len)
	{
		if (origin[s_i] != '\0' && (s_i == 0 || origin[s_i - 1] == '\0'))
		{
			res[res_i] = ft_strdup(&origin[s_i]);
			if (!res[res_i])
				return (return_with_free(res, origin, res_i + 1));
			res_i++;
		}
		s_i++;
	}
	res[res_i] = 0;
	if (origin)
	{
		free(origin);
		origin = NULL;
	}
	return (res);
}

static int	word_counter(char *origin, char c, size_t len)
{
	int		word_cnt;
	size_t	i;

	i = 0;
	word_cnt = 0;
	while (i < len)
	{
		if (origin[i] == c)
		{
			origin[i] = '\0';
			if (i != 0 && origin[i - 1] != '\0')
				word_cnt++;
		}
		i++;
	}
	if (i > 0 && origin[i - 1] != '\0')
		word_cnt++;
	return (word_cnt);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	char			*origin;
	size_t			s_len;
	int				word_cnt;

	word_cnt = 0;
	s_len = ft_strlen(s);
	origin = ft_strdup(s);
	if (!origin)
		return (0);
	word_cnt = word_counter(origin, c, s_len);
	res = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!res)
		return (return_with_free(res, origin, 0));
	return (sub_split(res, origin, s_len));
}
