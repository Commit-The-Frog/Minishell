/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:30:30 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/01 20:45:06 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_minishell.h"

char	is_operator(char c)
{
	const char	*control_operator[9] = {"|", "&", ";", "(", ")", "<", ">", "<<", ">>"};
	int			i;

	i = 0;
	while (i < 9)
	{
		// 한자리 연산자의 경우
		if (ft_strlen(control_operator[i]) == 1)
		{
			if (control_operator[i][0] == c)
				return (1);
		}
		else	// 2자리 이상의 연산자의 경우
		{
			if (ft_strchr(control_operator[i], c) != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 2)
		return (0);
	printf("%s\n", argv[1]);
	while (argv[1][i])
	{
		printf("%c is ", argv[1][i]);
		if (is_operator(argv[1][i]))
			printf("operator\n");
		else
			printf("not operator\n");
		i++;
	}
	return (0);
}
