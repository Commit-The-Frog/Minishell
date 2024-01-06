/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/06 21:12:33 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

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
void	exit_with_str(char *str, int custom_errno);
void	exit_custom_err(char *cmd, char *str, char *err_msg, int custom_errno);
int		print_custom_err(char *cmd, char *str, char *err_msg, int custom_errno);
void	redirect_input(char *file_name, int type);
void	redirect_output(char *file_name);
void	redirect_heredoc(char **deli, int cnt, char *start_dir);
void	redirect_append(char *file_name);
void	redirect_file(t_redir_node *redirect);
void	heredoc_sub_preprocess(t_redir_node *redirect, int *cnt, char *start_dir);
void	heredoc_preprocess(t_pipe_node *head, int *cnt, char *start_dir);
void	unlink_tmpfile(int cnt, char *start_dir);
void	*get_builtin_func(char *func);
int		is_builtin_cmd(t_cmd_node *cmd);
int		run_builtin_cmds(char **argv, t_dict **env_dict);
int		get_proc_cnt(t_pipe_node *head);
char	**get_bin_path_list(char *path);
char	*get_bin_path(char	*bin_name, t_dict **env_dict);
void	init_pipe(int *pipe_fd, t_pipe_node *next_pipe);
char	**generate_envp(t_dict *env_dict);
t_dict	*get_node_with_key(t_dict *list, char *key);
void	del_node_with_key(t_dict **env_dict, char *key);
char	*get_value_with_key(t_dict *list, char *key);
#endif
