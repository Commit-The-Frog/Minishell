/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:30:12 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 20:31:17 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TYPE_H
# define MINI_TYPE_H

enum e_token_type {
    E_TYPE_AMPERSAND = 0,
    E_TYPE_DOUBLE_AMPERSAND,
    E_TYPE_DOUBLE_PIPE,
    E_TYPE_PIPE,
    E_TYPE_SIMPLE_CMD,
    E_TYPE_REDIR_APPEND,
    E_TYPE_REDIR_HEREDOC,
    E_TYPE_REDIR_RIGHT,
	E_TYPE_REDIR_LEFT,
    E_TYPE_WHITESPACE,
    E_TYPE_DEFAULT,
	E_TYPE_SEMICOLON
}	t_token_type;

typedef struct	s_token
{
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct	s_redir_node
{
	int					type;
	char				*file_name;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct	s_simple_cmd_node
{
	char						*argv;
	struct s_simple_cmd_node	*next;
}	t_simple_cmd_node;

typedef struct	s_cmd_node
{
	t_redir_node		*redirect;
	t_simple_cmd_node	*simple_cmd;
	char				**argv;
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

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}	t_dict;

#endif
