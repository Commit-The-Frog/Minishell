/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:04 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/11 17:26:51 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_EXEC_H
# define MINI_EXEC_H

// ========= minishell_util.c =========
void	free_double_ptr(char **ptr);
int		ft_strcmp(char *s1, char *s2);

// ========= builtin_dir =========
int		ft_echo(char **argv, t_dict **env_dict);
int		ft_export(char **argv, t_dict **env_dict);
int		ft_cd(char **argv, t_dict **env_dict);
int		ft_pwd(char **argv, t_dict **env_dict);
int		ft_unset(char **argv, t_dict **env_dict);
int		ft_env(char **argv, t_dict **env_dict);
int		ft_exit(char **argv, t_dict **env_dict);

// ========= builtin_utils.c =========
void	*get_builtin_func(char *func);
int		is_builtin_cmd(t_cmd_node *cmd);
int		run_builtin(t_cmd_node *cmd, t_dict **env_dict, \
						int tmp_cnt, char *tmp_dir);

// ========= dict_utils.c =========
t_dict	*get_node_with_key(t_dict *list, char *key);
char	*get_value_with_key(t_dict *list, char *key);
void	del_node_with_key(t_dict **env_dict, char *key);

// ========= dict.c =========
t_dict	*create_dict_node_env(char *env);
void	add_node_back(t_dict **list, char *env);
t_dict	*dict_init(char	**envp);

// ========= envp_util.c =========
char	**generate_envp(t_dict *env_dict);
int		invalid_id_err(char *func_name, char *str);

// ========= exec_errhandle.c =========
void	exit_custom_err(char *cmd, char *str, char *err_msg, int custom_errno);
int		print_custom_err(char *cmd, char *str, char *err_msg, int custom_errno);

// ========= exec_heredoc_util.c =========
void	heredoc_sub_preprocess(t_redir_node *redirect, \
								char *start_dir, int get_input, t_dict **dict);
void	heredoc_preprocess(t_pipe_node *head, \
								char *start_dir, int get_input, t_dict **dict);
char	*heredoc_expand_str(char *origin, t_dict *env_dict);

// ========= exec_heredoc.c =========
void	redirect_heredoc(char **deli, char *start_dir, \
						int get_input, t_dict **dict);

// ========= exec_main.c =========
int		execute_main(t_pipe_node *head, t_dict **env_dict, char *start_dir);

// ========= exec_utils.c =========
int		is_path(char *str);
int		return_child_state(t_pstat *pstat, int proc_cnt, \
							char *start_dir);
int		get_proc_cnt(t_pipe_node *head);
char	**get_bin_path_list(char *path);
char	*get_bin_path(char	*bin_name, t_dict **env_dict);

// ========= heredoc_util.c =========
int		process_heredoc_fork(t_pipe_node *head, char *start_dir, t_dict **dict);
int		get_heredoc_file_cnt(t_pipe_node *head);
void	unlink_tmpfile(int cnt, char *start_dir);

// ========= redirect_io.c =========
int		redirect_input(char *file_name, int is_builtin);
int		redirect_output(char *file_name, int is_builtin);
int		redirect_append(char *file_name, int is_builtin);
int		redirect_file(t_redir_node *redirect, int is_builtin);
void	init_pipe(int *pipe_fd, t_pipe_node *next_pipe);

#endif
