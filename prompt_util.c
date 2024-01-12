/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 22:11:21 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 15:10:25 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_off_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	turn_on_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
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

void	free_ast(t_pipe_node **ast)
{
	t_pipe_node			*tmp;
	t_pipe_node			*target;
	t_cmd_node			*c_node;

	tmp = *ast;
	while (tmp)
	{
		c_node = tmp->cmd;
		if (c_node)
		{
			free_redir_node(c_node->redirect);
			free_double_ptr(c_node->argv);
			free_simple_cmd_node(c_node->simple_cmd);
			free(c_node);
		}
		target = tmp;
		tmp = tmp->next_pipe;
		free(target);
	}
	*ast = NULL;
}
