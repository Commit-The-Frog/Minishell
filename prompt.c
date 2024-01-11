/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 22:26:59 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_recent_exit(int recent_exit, t_dict **env_dict)
{
	char	*recent_exit_str;
	char	*recent_exit_env;

	recent_exit_str = ft_itoa(recent_exit);
	if (!recent_exit_str)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	recent_exit_env = ft_strjoin("?=", recent_exit_str);
	if (!recent_exit_env)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	add_node_back(env_dict, recent_exit_env);
	free(recent_exit_str);
	free(recent_exit_env);
}

static int	get_line_return_ast(int recent_exit, \
										t_dict **env_dict, t_pipe_node **ast)
{
	const char	*prompt = "minishell-2.0$ ";
	char		*line;
	int			err_flag;

	err_flag = 0;
	switch_signal_handler(0);
	restore_recent_exit(recent_exit, env_dict);
	line = readline(prompt);
	if (!line)
	{
		printf("exit\n");
		exit(recent_exit);
	}
	add_history(line);
	if (ft_sigismember(&g_recent_sig, SIGINT))
	{
		sigemptyset(&g_recent_sig);
		restore_recent_exit(1, env_dict);
	}
	err_flag = parse(line, *env_dict, ast);
	free(line);
	return (err_flag);
}

void	fuck(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char **envp)
{
	int			recent_exit;
	t_pipe_node	*ast;
	t_dict		*env_dict;
	int			err_flag;

	sigemptyset(&g_recent_sig);
	env_dict = dict_init(envp);
	recent_exit = 0;
	turn_off_ctrl();
	while (1)
	{
		err_flag = get_line_return_ast(recent_exit, &env_dict, &ast);
		if (err_flag == -1)
		{
			recent_exit = 1;
			continue ;
		}
		turn_on_ctrl();
		recent_exit = execute_main(ast, &env_dict);
		turn_off_ctrl();
		free_ast(&ast);
	}
	free_ast(&ast);
	rl_clear_history();
	exit(recent_exit);
}
