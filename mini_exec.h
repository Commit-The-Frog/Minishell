/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 11:44:13 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include "demo_minishell.h"

typedef struct	s_redirect_node
{
	int						type;
	char					*file_name;
	struct s_redirect_node	*left;
	struct s_redirect_node	*right;
}	t_redirect_node;

typedef struct	s_simple_cmd_node
{
	char	*path;
	char	**argv;
}	t_simple_cmd_node;

typedef struct	s_cmd_node
{
	t_redirect_node		*redirect;
	t_simple_cmd_node	*simple_cmd;
}	t_cmd_node;

typedef struct	s_pipe_node
{
	t_cmd_node			*cmd;
	struct s_pipe_node	*next_pipe;
}	t_pipe_node;

typedef struct	s_pstat
{
	pid_t	pid;
	int		exit_stat;
}	t_pstat;

typedef enum	e_redirect_type
{
	T_INPUT,
	T_OUTPUT,
	T_APPEND,
	T_HEREDOC
}	t_redirect_type;

#endif
