/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/02 22:12:38 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include "minishell.h"

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

typedef struct s_dict
{
	char			*key;
	char			*value;
	char			*env;
	struct s_dict	*next;
}	t_dict;

char	**generate_envp(t_dict *env_dict);
t_dict	*dict_init(char	**envp);
void	add_node_back(t_dict **list, char *key, char *value);
t_dict	*get_node_with_key(t_dict *list, char *key);
void	free_double_ptr(char **ptr);
#endif
