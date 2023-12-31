/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:40:55 by minjacho          #+#    #+#             */
/*   Updated: 2023/10/13 12:25:52 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	recur_put(char *str, int n, size_t *i)
{
	if (n == 0)
		return ;
	recur_put(str, n / 10, i);
	if (n < 0)
		str[*i] = '0' - n % 10;
	else
		str[*i] = '0' + n % 10;
	*i += 1;
}

char	*ft_itoa(int n)
{
	const size_t	str_len = int_len(n);
	size_t			i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (0);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (n < 0)
		str[i++] = '-';
	recur_put(str, n, &i);
	str[i] = '\0';
	return (str);
}
