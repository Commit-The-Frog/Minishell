/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkim2 <junkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 13:16:47 by junkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

# include "minishell.h"

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
