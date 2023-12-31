/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/31 17:18:54 by minjacho         ###   ########.fr       */
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
		// do nothing
	}
}

int main()
{
	static int	recent_exit = 0;
	const char	*prompt = "minishell$ ";
	char		*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n"); // test_mini$ exit으로 표시되어야 됨.
			break ;
		}
		add_history(line);
		free(line);
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			printf("exit\n");
			break ;
		}
	}
	rl_clear_history();
	exit(WEXITSTATUS(recent_exit));
}
