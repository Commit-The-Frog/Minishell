/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 15:50:39 by minjacho         ###   ########.fr       */
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

static t_pipe_node	*get_line_return_ast(int recent_exit, t_dict **env_dict)
{
	const char	*prompt = "minishell-2.0$ ";
	char		*line;
	t_pipe_node	*ast;

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
	ast = parse(line, *env_dict);
	free(line);
	return (ast);
}

int	main(int argc, char *argv[], char **envp)
{
	int			recent_exit;
	t_pipe_node	*ast;
	t_dict		*env_dict;

	sigemptyset(&g_recent_sig);
	env_dict = dict_init(envp);
	recent_exit = 0;
	turn_off_ctrl();
	while (1)
	{
		ast = get_line_return_ast(recent_exit, &env_dict);
		if (ast == NULL)
			continue ;
		turn_on_ctrl();
		recent_exit = execute_main(ast, &env_dict);
		turn_off_ctrl();
		free_ast(&ast);
	}
	free_ast(&ast);
	rl_clear_history();
	exit(recent_exit);
}
