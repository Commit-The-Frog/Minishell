/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:10:21 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:45:14 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	recur_unum_put(unsigned int n, int *size)
{
	char	c;
	int		w_size;

	if (n == 0)
		return (0);
	if (recur_unum_put(n / 10, size) < 0)
		return (-1);
	c = '0' + n % 10;
	w_size = write(1, &c, 1);
	*size += w_size;
	return (w_size);
}

static int	recur_put(int n, int *size)
{
	char	c;
	int		w_size;

	if (n == 0)
		return (0);
	if (recur_put(n / 10, size) < 0)
		return (-1);
	if (n < 0)
		c = '0' - n % 10;
	else
		c = '0' + n % 10;
	w_size = write(1, &c, 1);
	*size += w_size;
	return (w_size);
}

int	ft_printunbr(unsigned int num, int *size)
{
	int		w_size;

	if (num == 0)
	{
		w_size = write(1, "0", 1);
		*size += w_size;
	}
	else
		w_size = recur_unum_put(num, size);
	return (w_size);
}

int	ft_printnbr(int num, int *size)
{
	int		w_size;

	w_size = 0;
	if (num < 0)
	{
		w_size = write(1, "-", 1);
		*size += w_size;
	}
	if (w_size < 0)
		return (-1);
	if (num == 0)
	{
		w_size = write(1, "0", 1);
		*size += w_size;
	}
	else
		w_size = recur_put(num, size);
	return (w_size);
}
