/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 12:20:24 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/07 19:05:02 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(void)
{
	system("leaks a.out");
}

void	free_redir_node(t_redir_node *r_node)
{
	t_redir_node	*target;
	t_redir_node	*tmp;

	tmp = r_node;
	while (tmp)
	{
		target = tmp;
		tmp = tmp->next;
		free(target->file_name);
		free(target);
	}
}

void	free_simple_cmd_node(t_simple_cmd_node *r_node)
{
	t_simple_cmd_node	*target;
	t_simple_cmd_node	*tmp;

	tmp = r_node;
	while (tmp)
	{
		target = tmp;
		tmp = tmp->next;
		free(target->argv);
		free(target);
	}
}

void	free_ast(t_pipe_node *ast)
{
	t_pipe_node			*tmp;
	t_pipe_node			*target;
	t_cmd_node			*c_node;

	tmp = ast;
	while (tmp)
	{
		c_node = tmp->cmd;
		free_redir_node(c_node->redirect);
		free_double_ptr(c_node->argv);
		free_simple_cmd_node(c_node->simple_cmd);
		free(c_node);
		target = tmp;
		tmp = tmp->next_pipe;
		free(target);
	}
}

int main(int argc, char *argv[], char **envp)
{
	const char	*prompt = "minishell-2.0$ ";
	int			recent_exit = 0;
	char		*recent_exit_str;
	char		*recent_exit_env;
	char		*line;
	t_pipe_node *ast;
	t_dict		*env_dict;

	// atexit(f);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	env_dict = dict_init(envp);
	recent_exit_str = ft_itoa(recent_exit);
	if (!recent_exit_str)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	recent_exit_env = ft_strjoin("?=", recent_exit_str);
	if (!recent_exit_env)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	add_node_back(&env_dict, recent_exit_env);
	free(recent_exit_str);
	free(recent_exit_env);
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
		ast = parse(line, env_dict);
		if (ast == NULL)
			continue ;
		free(line);
		recent_exit = execute_main(ast, &env_dict);
		// printf("recent exit : %d\n", recent_exit);
		recent_exit_str = ft_itoa(recent_exit);
		if (!recent_exit_str)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		recent_exit_env = ft_strjoin("?=", recent_exit_str);
		if (!recent_exit_env)
			exit_custom_err(NULL, NULL, "Malloc error", 1);
		add_node_back(&env_dict, recent_exit_env);
		free(recent_exit_str);
		free(recent_exit_env);
		free_ast(ast);
	}
	free_ast(ast);
	rl_clear_history();
	exit(recent_exit);
}
