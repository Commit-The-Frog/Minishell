/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:24:02 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 14:39:03 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sigismember(sigset_t *dst_set, int signo)
{
	sigset_t	now_sigset;

	sigemptyset(&now_sigset);
	sigaddset(&now_sigset, signo);
	if ((*dst_set & now_sigset) == now_sigset)
		return (1);
	else
		return (0);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		sigaddset(&recent_sig, signo);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		sigaddset(&recent_sig, signo);
		rl_redisplay();
	}
}

void	sig_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		sigaddset(&recent_sig, signo);
		printf("\n");
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		sigaddset(&recent_sig, signo);
		rl_redisplay();
	}
}

void	sig_fork_handler(int signo)
{
	if (signo == SIGINT)
	{
		sigaddset(&recent_sig, signo);
		printf("\n");
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		sigaddset(&recent_sig, signo);
		printf("Quit\n");
		rl_redisplay();
	}
}

void	switch_signal_handler(int forked)
{
	if (forked)
	{
		signal(SIGINT, sig_fork_handler);
		signal(SIGQUIT, sig_fork_handler);
	}
	else
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
}
