/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 16:47:04 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **envp)
{
	const char	*prompt = "minishell-2.0$ ";
	int			recent_exit = 0;
	char		*line;
	t_pipe_node *ast;
	t_dict		*env_dict;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	env_dict = dict_init(envp);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		line = readline(prompt);
		// printf("[%s]\n", line);
		if (!line)
		{
			printf("exit\n"); // test_mini$ exit으로 표시되어야 됨.
			break ;
		}
		add_history(line);
		ast = parse(line);
		free(line);
		recent_exit = execute_main(ast, &env_dict);
	}
	rl_clear_history();
	exit(WEXITSTATUS(recent_exit));
}
