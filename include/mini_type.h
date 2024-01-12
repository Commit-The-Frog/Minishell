/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_type.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 20:30:12 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 20:13:19 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TYPE_H
# define MINI_TYPE_H

enum e_token_type {
	E_TYPE_AMPERSAND = 0,
	E_TYPE_DOUBLE_AMPERSAND = 1,
	E_TYPE_DOUBLE_PIPE = 2,
	E_TYPE_PIPE = 3,
	E_TYPE_SIMPLE_CMD = 4,
	E_TYPE_REDIR_APPEND = 5,
	E_TYPE_REDIR_HEREDOC = 6,
	E_TYPE_REDIR_RIGHT = 7,
	E_TYPE_REDIR_LEFT = 8,
	E_TYPE_WHITESPACE = 9,
	E_TYPE_DEFAULT = 10,
	E_TYPE_SEMICOLON = 11,
	E_TYPE_EXPAND = 12
}	t_token_type;

typedef struct s_token
{
	int				type;
	char			*str;
	char			*origin;
	struct s_token	*next;
}	t_token;

typedef struct s_redir_node
{
	int					type;
	char				*file_name;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct s_simple_cmd_node
{
	int							is_expand;
	char						*argv;
	struct s_simple_cmd_node	*next;
}	t_simple_cmd_node;

typedef struct s_cmd_node
{
	t_redir_node		*redirect;
	t_simple_cmd_node	*simple_cmd;
	char				**argv;
}	t_cmd_node;

typedef struct s_pipe_node
{
	t_cmd_node			*cmd;
	struct s_pipe_node	*next_pipe;
}	t_pipe_node;

typedef struct s_pstat
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
