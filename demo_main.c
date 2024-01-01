/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/01 15:25:07 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "demo_minishell.h"

int main()
{
	static int	recent_exit = 0;
	const char	*prompt = "minishell-1.0$ ";
	char		*line;
	pid_t		pid;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
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
		if (ft_strncmp(line, "cat", 4) == 0)
		{
			signal(SIGINT, sig_fork_handler);
			signal(SIGQUIT, sig_fork_handler);
			pid = fork();
			if (pid == 0)
				execve("/bin/cat", NULL, NULL);
			else
			{
				waitpid(pid, &recent_exit, 0);
			}
		}
		if (ft_strncmp(line, "sleep", 4) == 0)
		{
			signal(SIGINT, sig_fork_handler);
			signal(SIGQUIT, sig_fork_handler);
			pid = fork();
			char	*sleep_arg[2] = {"sleep", "5"};
			if (pid == 0)
				execve("/bin/sleep", sleep_arg, NULL);
			else
			{
				waitpid(pid, &recent_exit, 0);
			}
		}
	}
	rl_clear_history();
	exit(WEXITSTATUS(recent_exit));
}
