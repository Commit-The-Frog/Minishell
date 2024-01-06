/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:24:02 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 22:13:08 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	// ^C 뜨는거 없애고 새로운 줄로 출력할 필요.
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	sig_fork_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		printf("Quit\n");
		rl_redisplay();
	}
}
