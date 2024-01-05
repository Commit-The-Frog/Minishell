/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dequote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:58:25 by junkim2           #+#    #+#             */
/*   Updated: 2024/01/02 22:12:53 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == 0)
				return (0);
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

void	get_more_input(char **origin)
{
	char	*buff;
	char	*joined_str;

	while (!check_quote(*origin))
	{
		buff = readline("> ");
		joined_str = ft_strjoin(*origin, buff);
		free(*origin);
		free(buff);
		*origin = joined_str;
	}
}


void	check_leak(void)
{
	system("leaks a.out");
}

int	main(void)
{
	char	*origin;
	t_list	*token_list;
	t_list	*cur;

	// atexit(check_leak);
	printf("\033[0;32m");
	origin = readline("minishell> ");
	get_more_input(&origin);
	tokenize(&token_list, origin);
	cur = token_list;
	while (cur)
	{
		if (ft_strlen((char *)cur->content) > 0)
			printf("[%s] ", (char *)cur->content);
		cur = cur->next;
	}
	printf("\n");
	printf("\033[0m");
	free(origin);
}
