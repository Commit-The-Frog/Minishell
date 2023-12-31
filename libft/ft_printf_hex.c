/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:54:18 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:45:07 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recur_hex_put(unsigned long long n, int upper, int *size)
{
	char	c;
	int		w_size;

	if (n == 0)
		return (0);
	if (recur_hex_put(n / 16, upper, size) < 0)
		return (-1);
	c = '0' + n % 16;
	if (c > '9')
	{
		if (upper)
			c += 'A' - ('9' + 1);
		else
			c += 'a' - ('9' + 1);
	}
	w_size = write(1, &c, 1);
	if (w_size < 0)
		return (-1);
	else
	{
		*size += w_size;
		return (0);
	}
}

int	ft_printptr(void *ptr, int *size)
{
	unsigned long long	ptr_num;
	int					w_size;

	ptr_num = (unsigned long long)ptr;
	w_size = write(1, "0x", 2);
	*size += w_size;
	if (w_size < 0)
		return (-1);
	if (ptr_num == 0)
	{
		w_size = write(1, "0", 1);
		*size += w_size;
	}
	else
		w_size = recur_hex_put(ptr_num, 0, size);
	return (w_size);
}

int	ft_printhex(unsigned int num, char c, int *size)
{
	int	upper;
	int	w_size;

	upper = (c == 'X');
	if (num == 0)
	{
		w_size = write(1, "0", 1);
		*size += w_size;
	}
	else
		w_size = recur_hex_put(num, upper, size);
	return (w_size);
}
