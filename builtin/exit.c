/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:18:03 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/04 17:52:48 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	return_numeric_err(const char *str)
{
	const char	*err_str = "numeric argument required\n";

	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	return (255);
}

int	exit_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return(return_numeric_err(str));
		num *= 10;
		num += (str[i] - '0') * sign;
		i++;
	}
	return (num);
}

int		ft_exit(char **argv, t_dict **env_dict)
{
	int			argc;
	const char	*err_str = "too many arguments\n";

	argc = 0;
	while (argv && argv[argc])
		argc++;
	write(STDOUT_FILENO, "exit\n", 5);
	if (argc > 2)
	{
		write(2, err_str, ft_strlen(err_str));
		//error message write
		return (1);
	}
	if (argc == 1)
		exit(0);
	else
		exit(exit_atoi(argv[1]));
}
