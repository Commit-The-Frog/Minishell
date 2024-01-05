/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 19:59:51 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/05 20:31:34 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_exec.h"

int main(int argc, char *argv[], char **envp)
{
	static int	recent_exit = 0;
	const char	*prompt = "minishell-2.0$ ";
	char		*line;
	t_pipe_node *head;
	t_dict	*env_dict;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	env_dict = dict_init(envp);
	head = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	head->cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	head->cmd->simple_cmd = (t_simple_cmd_node *)malloc(sizeof(t_simple_cmd_node));
	head->cmd->redirect = NULL;
	head->next_pipe = NULL;
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
		head->cmd->simple_cmd->argv = ft_split(line, ' ');
		add_history(line);
		free(line);
		recent_exit = execute_main(head, &env_dict);
		free_double_ptr(head->cmd->simple_cmd->argv);
	}
	rl_clear_history();
	exit(WEXITSTATUS(recent_exit));
}
