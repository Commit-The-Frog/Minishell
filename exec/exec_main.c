/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:37:17 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/10 13:26:17 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	secur_execve(char *bin_path, char **argv, t_dict *env_dict)
{
	struct stat	stat_buf;
	char		**envp;

	envp = generate_envp(env_dict);
	if (stat(bin_path, &stat_buf) < 0)
		exit_custom_err(NULL, bin_path, "stat function error", 1);
	if (S_ISDIR(stat_buf.st_mode))
		exit_custom_err(NULL, bin_path, "is a directory", 126);
	execve(bin_path, argv, envp);
}

void	execute_simple_cmd(t_cmd_node *cmd, t_dict **env_dict)
{
	char	*bin_path;
	int		exit_code;

	if (!cmd->argv || !cmd->argv[0] || ft_strlen(cmd->argv[0]) == 0)
		exit(EXIT_SUCCESS);
	exit_code = run_builtin(cmd, env_dict, 0, NULL);
	if (exit_code >= 0)
		exit(exit_code);
	if (is_path(cmd->argv[0]))
	{
		if (access(cmd->argv[0], F_OK) != 0)
			exit_custom_err(NULL, cmd->argv[0], \
				"No such file or directory", 127);
		if (access(cmd->argv[0], X_OK) != 0)
			exit_custom_err(NULL, cmd->argv[0], "Permission denied", 126);
		bin_path = cmd->argv[0];
	}
	else
	{
		bin_path = get_bin_path(cmd->argv[0], env_dict);
		if (!bin_path)
			exit_custom_err(NULL, cmd->argv[0], "command not found", 127);
	}
	secur_execve(bin_path, cmd->argv, *env_dict);
}

void	execute_child(t_cmd_node *cmd, int *pipe_fd, t_dict **env_dict)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit(EXIT_SUCCESS);
	if (pipe_fd[0] >= 0 && pipe_fd[1] >= 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			exit_custom_err(NULL, NULL, "Duplicate file error", 1);
		close(pipe_fd[1]);
	}
	if (cmd->redirect)
		redirect_file(cmd->redirect, 0);
	execute_simple_cmd(cmd, env_dict);
}

void	execute_pipe(t_pipe_node *head, t_dict **env_dict, t_pstat *pstat)
{
	t_pipe_node	*pipe_node;
	int			idx;
	int			pipe_fd[2];

	pipe_node = head;
	idx = 0;
	while (pipe_node)
	{
		init_pipe(pipe_fd, pipe_node->next_pipe);
		pstat[idx].pid = fork();
		if (pstat[idx].pid == 0)
			execute_child(pipe_node->cmd, pipe_fd, env_dict);
		if (pipe_node->next_pipe)
		{
			close(pipe_fd[1]);
			if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
				exit_custom_err(NULL, NULL, "Duplicate file error", 1);
			close(pipe_fd[0]);
		}
		pipe_node = pipe_node->next_pipe;
		idx++;
	}
}

int	execute_main(t_pipe_node *head, t_dict **env_dict)
{
	int			proc_cnt;
	t_pstat		*pstat;
	int			tmpfile_cnt;
	int			origin_stdin;
	char		*start_dir;

	start_dir = NULL;
	start_dir = getcwd(start_dir, 0);
	tmpfile_cnt = 0;
	if (process_heredoc_fork(head, &tmpfile_cnt, start_dir) != 0)
		return (1);
	switch_signal_handler(1);
	proc_cnt = get_proc_cnt(head);
	if (!start_dir)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	if (proc_cnt == 1 && is_builtin_cmd(head->cmd))
		return (run_builtin(head->cmd, env_dict, tmpfile_cnt, start_dir));
	pstat = (t_pstat *)ft_calloc(proc_cnt, sizeof(t_pstat));
	if (!pstat)
		exit_custom_err(NULL, NULL, "Malloc error", 1);
	origin_stdin = dup(STDIN_FILENO);
	execute_pipe(head, env_dict, pstat);
	dup2(origin_stdin, STDIN_FILENO);
	close(origin_stdin);
	return (return_child_state(pstat, proc_cnt, tmpfile_cnt, start_dir));
}
