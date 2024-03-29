/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:18:03 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 16:10:43 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	return_numeric_err(const char *str, int *custom_err)
{
	const char	*err_str = "numeric argument required\n";

	write(2, "minishell", ft_strlen("minishell"));
	write(2, ": ", 2);
	write(2, "exit", ft_strlen("exit"));
	write(2, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, ": ", ft_strlen(": "));
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	*custom_err = 255;
	return (255);
}

static int	has_overflow(long long num, int next_digit)
{
	long long	after_cal;

	after_cal = num * 10 + next_digit;
	if ((after_cal / 10 != num) || (after_cal % 10 != next_digit))
		return (1);
	else
		return (0);
}

static int	exit_atoi(const char *str, int *custom_err)
{
	int			i;
	long long	num;
	int			sign;

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
		if (!ft_isdigit(str[i]) || has_overflow(num, (str[i] - '0') * sign))
			return (return_numeric_err(str, custom_err));
		num *= 10;
		num += (str[i] - '0') * sign;
		i++;
	}
	return (num);
}

int	ft_exit(char **argv, t_dict **env_dict)
{
	int			argc;
	int			exit_code;
	int			custom_err;

	argc = 0;
	custom_err = 0;
	env_dict = NULL;
	while (argv && argv[argc])
		argc++;
	write(STDOUT_FILENO, "exit\n", 5);
	if (argc > 1)
	{
		exit_code = exit_atoi(argv[1], &custom_err);
		if (custom_err == 255)
			exit(255);
	}
	if (argc > 2)
		return (print_custom_err(NULL, \
			"exit", "too many arguments", 1));
	if (argc == 1)
		exit(0);
	else
		exit(exit_code);
}
