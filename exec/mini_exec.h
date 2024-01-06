/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 11:45:31 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include "minishell.h"
# include <sys/stat.h>

typedef struct	s_redirect_node
{
	int						type;
	char					*file_name;
	struct s_redirect_node	*next;
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
	struct s_dict	*next;
}	t_dict;

char	**generate_envp(t_dict *env_dict);
t_dict	*dict_init(char	**envp);
t_dict	*create_dict_node_env(char *env);
void	add_node_back(t_dict **list, char *env);
t_dict	*get_node_with_key(t_dict *list, char *key);
void	del_node_with_key(t_dict **env_dict, char *key);
void	free_double_ptr(char **ptr);
int		ft_strcmp(char *s1, char *s2);

int		ft_echo(char **argv, t_dict **env_dict);
int		ft_export(char **argv, t_dict **env_dict);
int		ft_cd(char **argv, t_dict **env_dict);
int		ft_pwd(char **argv, t_dict **env_dict);
int		ft_unset(char **argv, t_dict **env_dict);
int		ft_env(char **argv, t_dict **env_dict);
int		ft_exit(char **argv, t_dict **env_dict);

int		execute_main(t_pipe_node *head, t_dict **env_dict);
#endif
