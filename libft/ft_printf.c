/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:54:13 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/01 11:45:22 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printstr(char *str, int *size)
{
	int	w_size;

	if (!str)
		w_size = write(1, "(null)", 6);
	else
		w_size = write(1, str, ft_strlen(str));
	*size += w_size;
	return (w_size);
}

int	print_arg(va_list ap, char c, int *size)
{
	int				w_size;
	unsigned char	result;

	if (c == 'c')
	{
		result = (unsigned char)va_arg(ap, int);
		w_size = write(1, &result, 1);
		*size += w_size;
	}
	else if (c == 's')
		w_size = ft_printstr(va_arg(ap, char *), size);
	else if (c == 'p')
		w_size = ft_printptr(va_arg(ap, void *), size);
	else if (c == 'd' || c == 'i')
		w_size = ft_printnbr(va_arg(ap, int), size);
	else if (c == 'u')
		w_size = ft_printunbr(va_arg(ap, unsigned int), size);
	else if (c == 'x' || c == 'X')
		w_size = ft_printhex(va_arg(ap, unsigned int), c, size);
	else
	{
		w_size = write(1, "%", 1);
		*size += w_size;
	}
	return (w_size);
}

int	iter_str(char *ptr, va_list ap)
{
	int	before_pct;
	int	size;

	size = 0;
	before_pct = 0;
	while (*ptr)
	{
		if (before_pct)
		{
			if (print_arg(ap, *ptr, &size) < 0)
				return (-1);
			before_pct = 0;
		}
		else if (*ptr == '%')
			before_pct = 1;
		else
		{
			if (write(1, ptr, 1) < 0)
				return (-1);
			size += 1;
		}
		ptr++;
	}
	return (size);
}

int	ft_printf(const char *format, ...)
{
	char	*ptr;
	va_list	ap;
	int		size;

	ptr = (char *)format;
	va_start(ap, format);
	size = iter_str(ptr, ap);
	va_end(ap);
	return (size);
}
