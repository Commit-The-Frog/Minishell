/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandelr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:24:02 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/01 15:25:43 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_minishell.h"

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
